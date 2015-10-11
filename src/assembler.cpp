#include <string>
#include <vector>
#include <iostream>
#include <cmath>
#include <sstream>
#include <bitset>

#include "instructions.h"
#include "assembler.h"

void assembler::translateInstruction(std::vector<std::string> instruction) {
  // Try to find out which type instruction the given instruction is. Then if
  // there were no errors push the hex code representation onto the internal
  // vector of hex codes.
  if(instruction.size() <= 1) {
    hexCodes.push_back("ERROR");
  }
  else if(isRType(instruction)) {
    hexCodes.push_back(rTypeAssemble(instruction));
  }
  else if(isIType(instruction)) {
    hexCodes.push_back(iTypeAssemble(instruction));
  }
  else {
    hexCodes.push_back("ERROR");
  }
}

std::string assembler::rTypeAssemble(std::vector<std::string> instruction) {
// Build the string representation of our binary number instruction
  std::string ret;
  ret.reserve(32);

  ret.append("000000");
  auto search = registers.find(instruction[2]);
  ret.append(search->second);
  search = registers.find(instruction[3]);
  ret.append(search->second);
  search = registers.find(instruction[1]);
  ret.append(search->second);
  ret.append("00000");
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
  search = registers.find(instruction[1]);
  ret.append(search->second);
  search = registers.find(instruction[3]);
  ret.append(search->second);
  int address = std::stoi(instruction[2]);
  ret.append(std::bitset<16>(address).to_string());

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
    bool validOpCode = rType.find(instruction[0]) != rType.end();
    bool validRegisters = isRegister(instruction[1]) && isRegister(instruction[2]) && isRegister(instruction[3]);

    // Tell the function caller whether the given instruction is a valid r
    // type instruction or not.
    return validOpCode && validRegisters ? true : false;
  }
  else {
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
  ss << std::hex << set.to_ulong();
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
