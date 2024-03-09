#include "parser.h"
#include "string_utils.h"
#include <iostream>

Parser::Parser(std::ifstream &inputFileStream) {
    this->inputFile.clear();

    while (!inputFileStream.eof()) {
        std::string line;
        getline(inputFileStream, line);

        std::string trimmedLine = string_utils::trim(line);
        if (trimmedLine != "") {
            std::cout << line << '\n';
            inputFile.push_back(trimmedLine);
        }
    }
}

void Parser::parseError(const char *message) {
    throw std::runtime_error(message);
};

std::string Parser::parseOperation(std::string &str) {
    std::string match =
        string_utils::getRgx(str, string_utils::OPERATION_PATTERN);
    if (match.empty()) {
        parseError("invalid operation");
        return "";
    }

    str = str.substr(match.length());
    return match;
}

void Parser::parseWhitespace(std::string &str) {
    std::string match =
        string_utils::getRgx(str, string_utils::WHITESPACE_PATTERN);
    if (match.empty()) {
        parseError("invalid operation");
    }
    str = str.substr(match.length());
}

unsigned int Parser::parseRegister(std::string &str) {
    std::string match =
        string_utils::getRgx(str, string_utils::REGISTER_PATTERN);
    if (match.empty()) {
        parseError("invalid register");
    }

    str = str.substr(match.length());

    // TODO: add more register variants
    if (match == "zero") {
        return 0;
    }
    return (match[1] - '0');
}

void Parser::parseComma(std::string &str) {
    std::string match = string_utils::getRgx(str, string_utils::COMMA_PATTERN);
    if (match.empty()) {
        parseError("comma expected");
    }
    str = str.substr(match.length());
}

int Parser::parseImm(std::string &str) {
    std::string match = string_utils::getRgx(str, string_utils::IMM_PATTERN);
    if (match.empty()) {
        parseError("invalid imm");
    }

    str = str.substr(match.length());
    return std::stoi(match);
}

inline void printInst(Instruction &_inst) {
    std::cout << _inst.opName << "\nlabel(if it is): " << _inst.label
              << "\nrd: " << _inst.rd << "\nrs1: " << _inst.rs1
              << "\nrs2: " << _inst.rs2 << "\nimm: " << _inst.imm
              << "\noffset: " << _inst.offset << '\n';
}
