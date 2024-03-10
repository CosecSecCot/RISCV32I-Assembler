#ifndef _PARSER_H
#define _PARSER_H

#include <fstream>
#include <string>
#include <string_utils.h>
#include <vector>

struct Instruction {
    std::string opName;
    std::string label;
    unsigned int rd;
    unsigned int rs1;
    unsigned int rs2;
    int imm;
    int offset;
};

class Parser {
public:
    std::vector<std::string> inputFile;
    Parser(std::ifstream &inputFileStream);

    void parse();
    inline void parseError(const char *message);
    std::string parseOperation(std::string &str);
    void parseWhitespace(std::string &str);
    unsigned int parseRegister(std::string &str);
    void parseComma(std::string &str);
    int parseImm(std::string &str, unsigned int bitSize);
    void parseOpenParen(std::string &str);
    void parseCloseParen(std::string &str);
};

#endif
