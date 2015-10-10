#include <string>
#include <vector>
#include <iostream>
#include "instructions.h"
#include <cmath>
#include <sstream>
#include <bitset>

bool isRType(std::vector<std::string> instruction);
bool isIType(std::vector<std::string> instruction);
bool isJType(std::vector<std::string> instruction);
bool isRegister(std::string);
//Returned vector is the hex representation (in text) of the mips command
std::vector<std::string> translateInstructions(std::vector<std::string> instruction) {
  if(instruction.size() <= 1) {
    return {"Error"};
  }

  if(isRType(instruction)) {


  }

  return {""};
}

bool isRType(std::vector<std::string> instruction) {
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

bool isIType(std::vector<std::string> instruction) {
  if(instruction.size() == 4) {
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

bool isJType(std::vector<std::string> instruction) {
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

bool inline isRegister(std::string mipsRegister) {
  return registers.find(mipsRegister) != registers.end() ? true : false;
}

std::string binaryToHex(std::string binaryString) {
  std::stringstream ss;
  std::bitset<32> set(binaryString);
  std::string hexCode;

  ss << std::hex << set.to_ulong();
  ss >> hexCode;
  return hexCode;
}
