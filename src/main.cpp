#include "assembler.h"
#include "parser.h"
#include "fileWriter.h"
#include <vector>

int main(int argc, char* argv[]) {
  if (argc != 2) {

    std::vector<std::string> file = readFile(argv[1]);
    std::vector<std::vector<std::string> > parsedFile = parseFile(file);
    assembler assembler;

    for (auto i: parsedFile) {
      assembler.translateInstruction(i);
    }

    std::vector<std::string> hexCodes = assembler.getHexCodes();

    writeToFile(hexCodes, argv[2]);
  }
  else {
    std::cout << "Incorrect number of arguments" << std::endl;
  }
}

//100011 11111 11101 0000000000000000
