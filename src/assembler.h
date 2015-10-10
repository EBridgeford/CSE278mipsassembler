#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

#include <string>
#include <vector>
#include <iostream>
#include "instructions.h"
#include <cmath>

class assembler {
public:
  std::vector<std::string> translateInstruction(std::vector<std::string> instruction);
  bool isRType(std::vector<std::string> instruction);
  bool isIType(std::vector<std::string> instruction);
  bool isJType(std::vector<std::string> instruction);
  bool isRegister(std::string);
private:
  std::vector<std::string> hexCodes;
};
#endif
