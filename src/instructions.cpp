#include <map>
#include <string>
#include <vector>
#include <iostream>
#include "instructions.h"

void iTypeAssemble (std::vector<std::string> instruction) {

  auto search = iType.find(instruction[0]);
  std::string opcode = search->second;

  search = registers.find(instruction[1]);
  std::string rs = search->second;
  
  search = registers.find(instruction[2]);
  std::string rt = search->second;

  std::string addr = instruction[3];

  std::cout << opcode+rs+rt+addr << std::endl;
}

void rTypeAssemble (std::vector<std::string> instruction) {


}
