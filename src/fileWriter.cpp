#include <fstream>
#include <vector>
#include <string>
#include "fileWriter.h"

void writeToFile(std::vector<std::string> hexCode, std::string filename) {
  std::ofstream output;
  output.open(filename+".txt");

  if (output.is_open() ) {
    for (auto i: hexCode) {
      output << "0x";
      output << i << std::endl;
    }
  }
  output.close();
}
