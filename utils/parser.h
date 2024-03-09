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

    inline void parseError(const char *message);
    inline std::string parseOperation(std::string &str);
    inline void parseWhitespace(std::string &str);
    inline unsigned int parseRegister(std::string &str);
    inline void parseComma(std::string &str);
    inline int parseImm(std::string &str);
};

#endif
