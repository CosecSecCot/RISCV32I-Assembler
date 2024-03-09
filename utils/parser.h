#ifndef _PARSER_H
#define _PARSER_H

#include <fstream>
#include <string>
#include <string_utils.h>
#include <vector>

class Parser {
public:
    std::vector<std::string> inputFile;
    Parser(std::ifstream &inputFileStream);
};

#endif
