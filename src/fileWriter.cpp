#include <fstream>
#include <vector>
#include <string>
#include "fileWriter.h"
#include <regex>

void fileWriter::writeToFile(std::vector<std::string> hexCode, std::string filename) {
  // Write the vector of hex codes to a .txt file.
  std::string fileNameWithExtension = filename;
  std::regex regularExpression = std::regex("\\.txt$");
  fileNameWithExtension += (std::regex_search(filename, regularExpression) ? "" : ".txt");
  
  std::ofstream output;
  output.open(fileNameWithExtension);
  if (output.is_open() ) {
    for (auto i: hexCode) {
      output << "0x";
      output << i << std::endl;
    }
  }
  output.close();
}
