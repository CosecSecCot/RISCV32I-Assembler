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

void Parser::parse() {
    for (auto line : inputFile) {
        std::string tmp_line(line);
        std::string op =
            string_utils::getRgx(tmp_line, string_utils::OPERATION_PATTERN);
        if (op == "addi") {
            try {
                Instruction inst;
                inst.opName = parseOperation(tmp_line);
                parseWhitespace(tmp_line);
                inst.rd = parseRegister(tmp_line);
                parseComma(tmp_line);
                inst.rs1 = parseRegister(tmp_line);
                parseComma(tmp_line);
                inst.imm = parseImm(tmp_line);

                printInst(inst);
            } catch (const std::exception &e) {
                std::cerr << e.what() << '\n';
                break;
            }
        } else if (op == "sub") {
            try {
                Instruction inst;
                inst.opName = parseOperation(tmp_line);
                parseWhitespace(tmp_line);
                inst.rd = parseRegister(tmp_line);
                parseComma(tmp_line);
                inst.rs1 = parseRegister(tmp_line);
                parseComma(tmp_line);
                inst.rs2 = parseRegister(tmp_line);

                printInst(inst);
            } catch (const std::exception &e) {
                std::cerr << e.what() << '\n';
                break;
            }
        } else if (op == "slt") {
            try {
                Instruction inst;
                inst.opName = parseOperation(tmp_line);
                parseWhitespace(tmp_line);
                inst.rd = parseRegister(tmp_line);
                parseComma(tmp_line);
                inst.rs1 = parseRegister(tmp_line);
                parseComma(tmp_line);
                inst.rs2 = parseRegister(tmp_line);

                printInst(inst);
            } catch (const std::exception &e) {
                std::cerr << e.what() << '\n';
                break;
            }
        } else if (op == "sltu") {
            try {
                Instruction inst;
                inst.opName = parseOperation(tmp_line);
                parseWhitespace(tmp_line);
                inst.rd = parseRegister(tmp_line);
                parseComma(tmp_line);
                inst.rs1 = parseRegister(tmp_line);
                parseComma(tmp_line);
                inst.rs2 = parseRegister(tmp_line);

                printInst(inst);
            } catch (const std::exception &e) {
                std::cerr << e.what() << '\n';
                break;
            }
        } else if (op == "xor") {
            try {
                Instruction inst;
                inst.opName = parseOperation(tmp_line);
                parseWhitespace(tmp_line);
                inst.rd = parseRegister(tmp_line);
                parseComma(tmp_line);
                inst.rs1 = parseRegister(tmp_line);
                parseComma(tmp_line);
                inst.rs2 = parseRegister(tmp_line);

                printInst(inst);
            } catch (const std::exception &e) {
                std::cerr << e.what() << '\n';
                break;
            }
        } else if (op == "sll") {
            try {
                Instruction inst;
                inst.opName = parseOperation(tmp_line);
                parseWhitespace(tmp_line);
                inst.rd = parseRegister(tmp_line);
                parseComma(tmp_line);
                inst.rs1 = parseRegister(tmp_line);
                parseComma(tmp_line);
                inst.rs2 = parseRegister(tmp_line);

                printInst(inst);
            } catch (const std::exception &e) {
                std::cerr << e.what() << '\n';
                break;
            }
        } else if (op == "srl") {
            try {
                Instruction inst;
                inst.opName = parseOperation(tmp_line);
                parseWhitespace(tmp_line);
                inst.rd = parseRegister(tmp_line);
                parseComma(tmp_line);
                inst.rs1 = parseRegister(tmp_line);
                parseComma(tmp_line);
                inst.rs2 = parseRegister(tmp_line);

                printInst(inst);
            } catch (const std::exception &e) {
                std::cerr << e.what() << '\n';
                break;
            }
        } else if (op == "or") {
            try {
                Instruction inst;
                inst.opName = parseOperation(tmp_line);
                parseWhitespace(tmp_line);
                inst.rd = parseRegister(tmp_line);
                parseComma(tmp_line);
                inst.rs1 = parseRegister(tmp_line);
                parseComma(tmp_line);
                inst.rs2 = parseRegister(tmp_line);

                printInst(inst);
            } catch (const std::exception &e) {
                std::cerr << e.what() << '\n';
                break;
            }
        } else if (op == "and") {
            try {
                Instruction inst;
                inst.opName = parseOperation(tmp_line);
                parseWhitespace(tmp_line);
                inst.rd = parseRegister(tmp_line);
                parseComma(tmp_line);
                inst.rs1 = parseRegister(tmp_line);
                parseComma(tmp_line);
                inst.rs2 = parseRegister(tmp_line);

                printInst(inst);
            } catch (const std::exception &e) {
                std::cerr << e.what() << '\n';
                break;
            }
        } else if (op == "sltiu") {
            try {
                Instruction inst;
                inst.opName = parseOperation(tmp_line);
                parseWhitespace(tmp_line);
                inst.rd = parseRegister(tmp_line);
                parseComma(tmp_line);
                inst.rs1 = parseRegister(tmp_line);
                parseComma(tmp_line);
                inst.imm = parseImm(tmp_line);

                printInst(inst);
            } catch (const std::exception &e) {
                std::cerr << e.what() << '\n';
                break;
            }
        } else if (op == "jalr") {
            try {
                Instruction inst;
                inst.opName = parseOperation(tmp_line);
                parseWhitespace(tmp_line);
                inst.rd = parseRegister(tmp_line);
                parseComma(tmp_line);
                inst.rs1 = parseRegister(tmp_line);
                parseComma(tmp_line);
                inst.offset = parseImm(tmp_line);

                printInst(inst);
            } catch (const std::exception &e) {
                std::cerr << e.what() << '\n';
                break;
            }
        } else if (op == "beq") {
            try {
                Instruction inst;
                inst.opName = parseOperation(tmp_line);
                parseWhitespace(tmp_line);
                inst.rs1 = parseRegister(tmp_line);
                parseComma(tmp_line);
                inst.rs2 = parseRegister(tmp_line);
                parseComma(tmp_line);
                inst.offset = parseImm(tmp_line);

                printInst(inst);
            } catch (const std::exception &e) {
                std::cerr << e.what() << '\n';
                break;
            }
        } else if (op == "bne") {
            try {
                Instruction inst;
                inst.opName = parseOperation(tmp_line);
                parseWhitespace(tmp_line);
                inst.rs1 = parseRegister(tmp_line);
                parseComma(tmp_line);
                inst.rs2 = parseRegister(tmp_line);
                parseComma(tmp_line);
                inst.offset = parseImm(tmp_line);

                printInst(inst);
            } catch (const std::exception &e) {
                std::cerr << e.what() << '\n';
                break;
            }
        } else if (op == "bge") {
            try {
                Instruction inst;
                inst.opName = parseOperation(tmp_line);
                parseWhitespace(tmp_line);
                inst.rs1 = parseRegister(tmp_line);
                parseComma(tmp_line);
                inst.rs2 = parseRegister(tmp_line);
                parseComma(tmp_line);
                inst.offset = parseImm(tmp_line);

                printInst(inst);
            } catch (const std::exception &e) {
                std::cerr << e.what() << '\n';
                break;
            }
        } else if (op == "bgeu") {
            try {
                Instruction inst;
                inst.opName = parseOperation(tmp_line);
                parseWhitespace(tmp_line);
                inst.rs1 = parseRegister(tmp_line);
                parseComma(tmp_line);
                inst.rs2 = parseRegister(tmp_line);
                parseComma(tmp_line);
                inst.offset = parseImm(tmp_line);

                printInst(inst);
            } catch (const std::exception &e) {
                std::cerr << e.what() << '\n';
                break;
            }
        } else if (op == "blt") {
            try {
                Instruction inst;
                inst.opName = parseOperation(tmp_line);
                parseWhitespace(tmp_line);
                inst.rs1 = parseRegister(tmp_line);
                parseComma(tmp_line);
                inst.rs2 = parseRegister(tmp_line);
                parseComma(tmp_line);
                inst.offset = parseImm(tmp_line);

                printInst(inst);
            } catch (const std::exception &e) {
                std::cerr << e.what() << '\n';
                break;
            }
        } else if (op == "bltu") {
            try {
                Instruction inst;
                inst.opName = parseOperation(tmp_line);
                parseWhitespace(tmp_line);
                inst.rs1 = parseRegister(tmp_line);
                parseComma(tmp_line);
                inst.rs2 = parseRegister(tmp_line);
                parseComma(tmp_line);
                inst.offset = parseImm(tmp_line);

                printInst(inst);
            } catch (const std::exception &e) {
                std::cerr << e.what() << '\n';
                break;
            }
        } else if (op == "auipc") {
            try {
                Instruction inst;
                inst.opName = parseOperation(tmp_line);
                parseWhitespace(tmp_line);
                inst.rd = parseRegister(tmp_line);
                parseComma(tmp_line);
                inst.imm = parseImm(tmp_line);

                printInst(inst);
            } catch (const std::exception &e) {
                std::cerr << e.what() << '\n';
                break;
            }
        } else if (op == "lui") {
            try {
                Instruction inst;
                inst.opName = parseOperation(tmp_line);
                parseWhitespace(tmp_line);
                inst.rd = parseRegister(tmp_line);
                parseComma(tmp_line);
                inst.imm = parseImm(tmp_line);

                printInst(inst);
            } catch (const std::exception &e) {
                std::cerr << e.what() << '\n';
                break;
            }
        } else if (op == "jal") {
            try {
                Instruction inst;
                inst.opName = parseOperation(tmp_line);
                parseWhitespace(tmp_line);
                inst.rd = parseRegister(tmp_line);
                parseComma(tmp_line);
                inst.offset = parseImm(tmp_line);

                printInst(inst);
            } catch (const std::exception &e) {
                std::cerr << e.what() << '\n';
                break;
            }
        } else if (op == "mul") {
            try {
                Instruction inst;
                inst.opName = parseOperation(tmp_line);
                parseWhitespace(tmp_line);
                inst.rd = parseRegister(tmp_line);
                parseComma(tmp_line);
                inst.rs1 = parseRegister(tmp_line);
                parseComma(tmp_line);
                inst.rs2 = parseRegister(tmp_line);

                printInst(inst);
            } catch (const std::exception &e) {
                std::cerr << e.what() << '\n';
                break;
            }
        } else {
            // parseError("invalid operation");
            std::cerr << '\n' << line << "\ninvalid operation\n";
            break;
        }
    }
}