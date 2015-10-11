#ifndef __Parser_H
#define __Parser_H


#include <vector>
#include <string>

std::vector<std::string> readFile(std::string filename);
std::vector< std::vector<std::string> > parseFile(std::vector<std::string> file);

#endif
