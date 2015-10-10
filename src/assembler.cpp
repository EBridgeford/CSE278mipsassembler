#include <string>
#include <vector>
#include <iostream>
#include <cmath>
#include <sstream>
#include <bitset>

#include "instructions.h"
#include "assembler.h"


//Returned vector is the hex representation (in text) of the mips command



void assembler::translateInstruction(std::vector<std::string> instruction) {


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

  ret = binaryToHex(ret);
  return ret;
}

std::string assembler::iTypeAssemble(std::vector<std::string> instruction) {

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

  ret = binaryToHex(ret);
  return ret;
}

bool assembler::isRType(std::vector<std::string> instruction) {
  if(instruction.size() == 4) {
    bool validOpCode = rType.find(instruction[0]) != rType.end();
    bool validRegisters = isRegister(instruction[1]) &&
                          isRegister(instruction[2]) &&
                          isRegister(instruction[3]);
    return validOpCode && validRegisters ? true : false;
  }
  else {
    return false;
  }
}

bool assembler::isIType(std::vector<std::string> instruction) {
 if (instruction.size() == 4) {
    bool validOpCode = iType.find(instruction[0]) != iType.end();
    int address;
    try {
      address = std::stoi(instruction[2]);
    }
    catch(std::exception e) {
      return false;
    }
    bool validAddress = address >= 0 && address <= (std::pow(2, 17) - 1);
    bool validRegisters = isRegister(instruction[1]) &&
                          isRegister(instruction[3]);
    return validOpCode && validAddress && validRegisters ? true : false;
  }
  else {
    return false;
  }
}

bool assembler::isJType(std::vector<std::string> instruction) {
  if(instruction.size() == 2) {
    bool validOpCode = jType.find(instruction[0]) != jType.end();
    int address;
    try {
      address = std::stoi(instruction[1]);
    }
    catch(std::exception e) {
      return false;
    }
    bool validAddress = address >= 0 && address <= (std::pow(2, 27) - 1);
    return validOpCode && validAddress ? true : false;
  }
  else {
    return false;
  }
}

bool assembler::isRegister(std::string mipsRegister) {
  return registers.find(mipsRegister) != registers.end() ? true : false;
}

std::string assembler::binaryToHex(std::string binaryString) {
  std::stringstream ss;
  std::bitset<32> set(binaryString);
  std::string hexCode;

  ss << std::hex << set.to_ulong();
  ss >> hexCode;
  return hexCode;
}

void assembler::printer() {

  for(auto i: hexCodes) {
    std::cout << i << std::endl;
  }
}

std::vector<std::string> assembler::getHexCodes() {
  return hexCodes;
}
