#ifndef _PARSER_H
#define _PARSER_H

#include <fstream>
#include <map>
#include <string>
#include <string_utils.h>
#include <vector>

struct Instruction {
    std::string opName;
    unsigned int rd = 0;
    unsigned int rs1 = 0;
    unsigned int rs2 = 0;
    int imm;
    int offset = 0;
};

class Parser {
public:
    std::vector<std::string> inputFile;
    Parser(std::ifstream &inputFileStream);
    std::map<std::string, unsigned int> labelLocations;

    void parse();
    inline void parseError(const char *message);
    std::string parseLabel(std::string &str);
    std::string parseOperation(std::string &str);
    void parseWhitespace(std::string &str);
    unsigned int parseRegister(std::string &str);
    void parseComma(std::string &str);
    int parseImm(std::string &str, unsigned int bitSize);
    void parseOpenParen(std::string &str);
    void parseCloseParen(std::string &str);
};

#endif
