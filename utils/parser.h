#ifndef _PARSER_H
#define _PARSER_H

#include <fstream>
#include <map>
#include <string>
#include <vector>

class Parser {
public:
    std::vector<std::string> inputFile;
    Parser(std::ifstream &inputFileStream);
    std::map<std::string, unsigned int> labelLocations;

    void parse();
    inline void parseError(const char *message);
    std::string parseLabelName(std::string &str);
    std::string parseLabel(std::string &str);
    std::string parseOperation(std::string &str);
    void parseWhitespace(std::string &str);
    unsigned int parseRegister(std::string &str);
    void parseComma(std::string &str);
    int parseImm(std::string &str, unsigned int bitSize);
    void parseOpenParen(std::string &str);
    void parseCloseParen(std::string &str);
    std::string parseRTypeInst(std::string opName, unsigned int rd,
                               unsigned int rs1, unsigned int rs2);
    std::string parseITypeInst(std::string opName, unsigned int rd,
                               unsigned int rs1, unsigned int imm);
    std::string parseSTypeInst(std::string opName, unsigned int rs1,
                               unsigned int rs2, unsigned int imm);
};

#endif
