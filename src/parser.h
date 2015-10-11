#ifndef PARSER_H
#define PARSER_H

#include <vector>
#include <string>

class parser{
public:
  std::vector<std::string> readFile(std::string filename);
  std::vector< std::vector<std::string> > parseFile(std::vector<std::string> file);
};
#endif
