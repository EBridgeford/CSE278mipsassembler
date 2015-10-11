#include <array>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <regex>

std::vector<std::string> readFile(std::string filename) {

  std::ifstream readFile;
  readFile.open(filename);
  std::string tempLine;
  std::vector<std::string> stringVector;

  while (!readFile.eof()) {
    getline(readFile, tempLine);
    stringVector.push_back(tempLine);
  }

  stringVector.shrink_to_fit();

  return stringVector;
}

//Returns a 2D vector of strings
std::vector< std::vector<std::string> > parseFile(std::vector<std::string> file) {

  std::vector< std::vector<std::string>> ret;

  for (int i = 0; i < file.size(); i++) {
    if (file[i] != "") {
      std::regex regularExpression(",?[[:s:]]*(\\$?[[:w:]]+)[[:s:]]*,?");
      std::sregex_iterator start (file[i].cbegin(), file[i].cend(), regularExpression);
      std::sregex_iterator end;

      ret.insert(ret.begin() + i, std::vector<std::string>());
      for (; start != end; start++) {
        ret[i].push_back(start->str(1));
      }
    }
  }

  return ret;
}
