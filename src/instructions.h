#include <map>
#include <string>
#include <utility>

std::map<std::string, std::string> iType
  {{"lw", "100011"},
  {"addi", "001000"},
  {"ori", "001101"},
  {"andi", "001100"},
  {"slti", "001010"},
  {"beq", "000100"},
  {"sw", "101011"}};


std::map<std::string, std::string> rType
  {{"or", "100101"},
  {"add", "100000"},
  {"sub", "100010"},
  {"slt", "101010"},
  {"sll", "000000"},
  {"srl", "000010"},
  {"jr", "001000"},
  {"and", "100100"}};

  std::map<std::string, std::string> jType
    {{"j", "000010"},
    {"jal", "000011"}};

std::map<std::string, std::string> registers

{{"$zero", "00000"}, //0
{"$at", "00001"}, //1
{"$v0", "00001"}, //2
{"$v1", "00011"}, //3
{"$a0", "00100"}, //4
{"$a1", "00101"}, //5
{"$a2", "00110"}, //6
{"$a3", "00111"},  //7
{"$t0", "01000"}, //8
{"$t1", "01001"}, //9
{"$t2", "01010"}, //10
{"$t3", "01011"}, //11
{"$t4", "01100"}, //12
{"$t5", "01101"}, //13
{"$t6", "01110"}, //14
{"$t7", "01111"}, //15
{"$s0", "10000"}, //16
{"$s1", "10001"}, //17
{"$s2", "10010"}, //18
{"$s3", "10011"}, //19
{"$s4", "10100"}, //20
{"$s5", "10101"}, //21
{"$s6", "10110"}, //22
{"$s7", "10111"}, //23
{"$t8", "11000"}, //24
{"$t9", "11001"}, //25
{"$k0", "11010"}, //26
{"$k1", "11011"}, //27
{"$gp", "11100"}, //28
{"$sp", "11101"}, //29
{"$fp", "11110"}, //30
{"$ra", "11111"}}; //31
