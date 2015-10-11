#ifndef ASSEMBLER_H
#define ASSEMBLER_H

#include <string>
#include <vector>
#include <iostream>
#include <cmath>

class assembler {
public:
  void translateInstruction(std::vector<std::string> instruction);
  std::vector<std::string> getHexCodes();
  void printer();
private:
  bool isRType(std::vector<std::string> instruction);
  bool isIType(std::vector<std::string> instruction);
  bool isJType(std::vector<std::string> instruction);
  bool isRegister(std::string);
  std::string rTypeAssemble(std::vector<std::string> instruction);
  std::string iTypeAssemble(std::vector<std::string> instruction);
  std::string binaryToHex(std::string binaryString);

  std::vector<std::string> hexCodes;
};
#endif
