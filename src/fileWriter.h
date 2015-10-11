#ifndef FILE_WRITER_H
#define FILE_WRITER_H
#include <vector>
#include <string>

class fileWriter {
public:
  void writeToFile(std::vector<std::string> hexCode, std::string filename);
};
#endif
