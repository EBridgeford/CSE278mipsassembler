#include <fstream>
#include <vector>
#include <string>
#include "fileWriter.h"

void fileWriter::writeToFile(std::vector<std::string> hexCode, std::string filename) {
  // Write the vector of hex codes to a .txt file.
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
