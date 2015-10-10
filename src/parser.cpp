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

  //lw $ra,0($sp)
  //sw $ra,0($sp)
  //add $a0,$v0,$zero
  //sub $a0,$v0,$zero
  //addi $t1, $t1, 1
  for (int i = 0; i < file.size(); i++) {
    if (file[i] != "") { // Say the character, then say how many
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

int main(int argc, char* argv[]) {
  std::vector<std::string> file = readFile("asm.txt");
  std::vector< std::vector<std::string> > ret = parseFile(file);
  for(auto i = ret.begin(); i != ret.end(); ++i) {
    for(auto j = i->begin(); j != i->end(); ++j) {
      std::cout << *j << " ";
    }
    std::cout << std::endl;
  }

}
