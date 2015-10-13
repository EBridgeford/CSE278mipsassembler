#include <array>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <regex>
#include "parser.h"

std::vector<std::string> parser::readFile(std::string filename) {
  // Read each line of the given file into a vector.
  std::ifstream readFile;
  readFile.open(filename);
  std::string tempLine;
  std::vector<std::string> stringVector;
  while (!readFile.eof()) {
    getline(readFile, tempLine);
    stringVector.push_back(tempLine);
  }

  // Shrink the vector and return it to the function caller.
  stringVector.shrink_to_fit();
  return stringVector;
}

std::vector< std::vector<std::string> > parser::parseFile(std::vector<std::string> file) {
  // Take a vector filled with the lines of a text file and make a two dimensional
  // vector from that. Each nested vector is contains the strings that make up an
  // instruction, ie...{"addi", "$t1", "$t1", "1"}).
  std::vector< std::vector<std::string>> ret;
  for (int i = 0; i < file.size(); i++) {
    if (file[i] != "") {
      std::regex regularExpression(",?[[:s:]]*(\\$?[[:w:]]+)[[:s:]]*,?");
      std::sregex_iterator start (file[i].cbegin(), file[i].cend(), regularExpression);
      std::sregex_iterator end;

      ret.insert(ret.begin() + i, std::vector<std::string>());
      for (int k = 0; start != end; start++, k++) {
        ret[i].push_back(start->str(1));

        if(k == 3) {
          try {
            std::stoi(start->str(1));

            std::string tempString = ret[i][ret[i].size() - 1];
            ret[i][ret[i].size() - 1] = ret[i][ret[i].size() - 2];
            ret[i][ret[i].size() - 2] = tempString;
          }
          catch(std::exception e) {}
        }
      }
      for(int a = 0; a < ret[i].size(); a++)
      {
        std::cout << ret[i][a] << "  ";
      }
      std::cout << std::endl;
    }
  }

  return ret;
}
