#include <array>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>


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

std::vector< std::vector<std::string>> ret(5);

for (int i = 0; i < file.size(); i++) {

  if (file[i] != "") {


        auto start = 0U;


        auto end = 0;

        bool done = false;
        for (int j = 1; done == false || file[i].size() < i; j++) {
            if (isspace(file[i].at(j))) {
              end = j;
              done = true;
            }
        }


        ret[i].push_back(file[i].substr(start, end));
        end + 1;
        std::string delimiter = ",";
        start = end + delimiter.length();
        end = file[i].find(delimiter, start);
        while (end != std::string::npos)
        {
            ret[i].push_back(file[i].substr(start, end - start));
            start = end + delimiter.length();
            end = file[i].find(delimiter, start);
        }

        ret[i].push_back(file[i].substr(start, end));
  }
}

return ret;
}



int main() {
  std::vector<std::string> file = readFile("asm.txt");
  std::vector< std::vector<std::string> > ret = parseFile(file);
  std::cout << ret[0][0] << std::endl;
  std::cout << ret[0][1] << std::endl;
  std::cout << ret[0][2] << std::endl;
  std::cout << ret[0][3] << std::endl;

}
