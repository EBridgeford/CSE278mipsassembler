#include <string>
#include <vector>
#include <iostream>
#include <cmath>
#include <sstream>
#include <bitset>
#include <iomanip>

#include "instructions.h"
#include "assembler.h"

void assembler::translateInstruction(std::vector<std::string> instruction) {
  // Try to find out which type instruction the given instruction is. Then if
  // there were no errors push the hex code representation onto the internal
  // vector of hex codes.
  std::string temp = " ";
  for(int i = 0; i < instruction.size(); i++) {
    temp += instruction[i] + " ";
  }

  if(instruction.size() <= 1) {} // This is a line or space. We just ignore it.
  else if(isRType(instruction)) {
    hexCodes.push_back(rTypeAssemble(instruction) + temp);
  }
  else if(isIType(instruction)) {
    hexCodes.push_back(iTypeAssemble(instruction) + temp);
  }
  else if (isJType(instruction)) {
    hexCodes.push_back(jTypeAssemble(instruction) + temp);
  }
  else {
    hexCodes.push_back("ERROR NOT A VALID TYPE" + temp);
  }
}

std::string assembler::rTypeAssemble(std::vector<std::string> instruction) {
  // Build the string representation of our binary number instruction
  std::string ret;
  ret.reserve(32);

  ret.append("000000");

  // rs is in the second position unless it is an jr instruction
  auto search = registers.find((instruction.size() == 2 ? instruction[1] : instruction[2]));
  if (search != registers.end()) {
    ret.append(search->second);
  } else {
    ret.append("00000");
  }

  if(instruction.size() == 4) {
    search = registers.find(instruction[3]);
    ret.append(search->second);

    search = registers.find(instruction[1]);
    ret.append(search->second);

    search = registers.find(instruction[2]);
    if (search == registers.end()) {
      try {
        int shamt = std::stoi(instruction[2]);
        ret.append(std::bitset<5>(shamt).to_string());
      }
      catch(std::exception e) {}
    } else {
      ret.append("00000");
    }
  }
  else {
    // 15 0's for jr special case
    ret.append("000000000000000");
  }

  search = rType.find(instruction[0]);
  ret.append(search->second);

  // Convert the string representation of a binary number into a string
  // representation of a hex number. Then return it to the function caller.
  ret = binaryToHex(ret);
  return ret;
}

std::string assembler::iTypeAssemble(std::vector<std::string> instruction) {
  // Build the string representation of our binary number instruction
  std::string ret;
  ret.reserve(32);

  auto search = iType.find(instruction[0]);
  ret.append(search->second);
  search = registers.find(instruction[3]);
  ret.append(search->second);
  search = registers.find(instruction[1]);
  ret.append(search->second);
  int address = std::stoi(instruction[2]);
  ret.append(std::bitset<16>(address).to_string());

  // Convert the string representation of a binary number into a string
  // representation of a hex number. Then return it to the function caller.
  ret = binaryToHex(ret);
  return ret;
}

std::string assembler::jTypeAssemble(std::vector<std::string> instruction) {
  // Build the string representation of our binary number instruction
  std::string ret;
  ret.reserve(32);

  auto search = jType.find(instruction[0]);
  ret.append(search->second);
  int address = std::stoi(instruction[1]);
  ret.append(std::bitset<26>(address).to_string());

  // Convert the string representation of a binary number into a string
  // representation of a hex number. Then return it to the function caller.
  ret = binaryToHex(ret);
  return ret;
}

bool assembler::isRType(std::vector<std::string> instruction) {
  // All r type instructions should have four strings.
  if(instruction.size() == 4) {
    // Try to find the given string representation of a opcode in our map of
    // all MIPS opcodes.
    bool secondCheck = isRegister(instruction[2]);

    if (secondCheck == false) {

      try {
        int shamt = std::stoi(instruction[2]);
        if (shamt <= (std::pow(2, 5) - 1)) {
          secondCheck = true;
        }
      }
      catch(std::exception e) {}
    }


    bool validOpCode = rType.find(instruction[0]) != rType.end();
    bool validRegisters = isRegister(instruction[1]) && secondCheck && isRegister(instruction[3]);

    // Tell the function caller whether the given instruction is a valid r
    // type instruction or not.
    return validOpCode && validRegisters ? true : false;
  }
  else {
    if(instruction.size() == 2) {
      bool validOpCode = rType.find(instruction[0]) != rType.end();
      bool validRegisters = isRegister(instruction[1]);
      return validOpCode && validRegisters ? true : false;
    }
    // Tell the function caller that the given instruction is not a valid r
    // type instruction.
    return false;
  }
}

bool assembler::isIType(std::vector<std::string> instruction) {
  // All i type instructions should have four strings.
  if (instruction.size() == 4) {
    // Try to find the given string representation of a opcode in our map of
    // all MIPS opcodes.
    bool validOpCode = iType.find(instruction[0]) != iType.end();

    // Convert the string representation of an address to an int. Then make
    // sure it is in the correct range.
    int address;
    try {
      address = std::stoi(instruction[2]);
    }
    catch(std::exception e) {
      return false;
    }
    bool validAddress = address >= 0 && address <= (std::pow(2, 17) - 1);

    // Try to find the given string representations of the given registers in
    // our map of all MIPS registers.
    bool validRegisters = isRegister(instruction[1]) && isRegister(instruction[3]);

    //std::cout << instruction[0];
    //std::cout << " Opcode " << validOpCode << " Address " << validAddress;
    //std::cout << " Registers " << validRegisters << std::endl;

    // Tell the function caller whether the given instruction is a valid i
    // type instruction or not.
    return validOpCode && validAddress && validRegisters ? true : false;
  }
  else {
    // Tell the function caller that the given instruction is not a valid i
    // type instruction.
    return false;
  }
}

bool assembler::isJType(std::vector<std::string> instruction) {
  // All j type instructions should have two strings.
  if(instruction.size() == 2) {
    // Try to find the given string representation of a opcode in our map of
    // all MIPS opcodes.
    bool validOpCode = jType.find(instruction[0]) != jType.end();

    // Convert the string representation of an address to an int. Then make
    // sure it is in the correct range.
    int address;
    try {
      address = std::stoi(instruction[1]);
    }
    catch(std::exception e) {
      return false;
    }
    bool validAddress = address >= 0 && address <= (std::pow(2, 27) - 1);

    // Tell the function caller whether the given instruction is a valid j
    // type instruction or not.
    return validOpCode && validAddress ? true : false;
  }
  else {
    // Tell the function caller that the given instruction is not a valid j
    // type instruction.
    return false;
  }
}

bool assembler::isRegister(std::string mipsRegister) {
  // Try to find the given string representation of a register in our map of
  // all MIPS registers.
  return registers.find(mipsRegister) != registers.end() ? true : false;
}

std::string assembler::binaryToHex(std::string binaryString) {
  // Convert the string representation of a binary number to hex.
  std::stringstream ss;
  std::bitset<32> set(binaryString);
  std::string hexCode;
  ss << std::setfill('0') << std::setw(8) << std::hex << set.to_ulong();
  ss >> hexCode;
  return hexCode;
}

void assembler::printer() {
  // Print out the internal vector containing hex codes.
  for(auto i: hexCodes) {
    std::cout << i << std::endl;
  }
}

std::vector<std::string> assembler::getHexCodes() {
  // Return the saved hex codes to the function caller.
  return hexCodes;
}
