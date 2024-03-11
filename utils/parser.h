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
    std::string outputFileContent;

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
    void computeRTypeInst(std::string &tmp_line);
    std::string parseITypeInst(std::string opName, unsigned int rd,
                               unsigned int rs1, int imm);
    void computeITypeInst(std::string &tmp_line);
    std::string parseSTypeInst(std::string opName, unsigned int rs1,
                               unsigned int rs2, int imm);
    std::string parseBTypeInst(std::string opName, unsigned int rs1,
                               unsigned int rs2, int offset);
    void computeBTypeInst(std::string &tmp_line, unsigned int lineNo);
    std::string parseUTypeInst(std::string opName, unsigned int rd, int imm);
    void computeUTypeInst(std::string &tmp_line);
    std::string parseJTypeInst(std::string opName, unsigned int rd, int imm);
    void computeJTypeInst(std::string &tmp_line, unsigned int lineNo);
};

#endif
