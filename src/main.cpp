#include "assembler.h"
#include "parser.h"
#include "fileWriter.h"
#include <vector>
#include <iostream>
#include <fstream>

int main(int argc, char* argv[]) {
  // If the program exits if it does not have the correct number of arguments.
  if (argc == 3) {
    // Check if the input file is valid before attempting to read it.
    std::ifstream inputFile(argv[1]);
    if(!inputFile.good()) {
      std::cout << "Invalid input file" << std::endl;
      std::cout << "Exiting..." << std::endl;
      return -1;
    }

    // Read the input file into a vector of vectors (each nested vector is contains
    // the strings that make up an instruction, ie...{"addi", "$t1", "$t1", "1"}).
    parser parser;
    std::vector<std::string> file = parser.readFile(argv[1]);
    std::vector<std::vector<std::string> > parsedFile = parser.parseFile(file);

    // The assembler object will remember each instruction that it converts to hex.
    // So, the following code will convert all of the instructions to hex, and then
    // it will retrieve the list of converted hex values.
    assembler assembler;
    for (auto i: parsedFile) {
      assembler.translateInstruction(i);
    }
    std::vector<std::string> hexCodes = assembler.getHexCodes();

    // Write the hex values to a .txt file.
    fileWriter fileWriter;
    fileWriter.writeToFile(hexCodes, argv[2]);
    return 0;
  }
  else {
    // Exit because the user did not give the correct number of arguments.
    std::cout << "Incorrect number of arguments" << std::endl;
    std::cout << "Exiting..." << std::endl;
    return -1;
  }
}

//100011 11111 11101 0000000000000000
