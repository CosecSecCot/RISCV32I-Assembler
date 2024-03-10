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
            this->inputFile.push_back(trimmedLine);
        }
    }
}

inline bool inRange(int x, int n) {
    return (-1 * std::pow(2, n - 1) <= x) && (x <= std::pow(2, n - 1) - 1);
}

void Parser::parseError(const char *message) {
    throw std::runtime_error(message);
};

std::string Parser::parseLabelName(std::string &str) {
    std::string match =
        string_utils::getRgx(str, string_utils::LABEL_NAME_PATTERN);
    if (match.empty()) {
        throw std::runtime_error("invalid label");
    }

    str = str.substr(match.length());
    return match;
}

std::string Parser::parseLabel(std::string &str) {
    std::string match = string_utils::getRgx(str, string_utils::LABEL_PATTERN);
    if (match.empty()) {
        return "";
    }

    str = str.substr(match.length());
    return match;
}

std::string Parser::parseOperation(std::string &str) {
    std::string match =
        string_utils::getRgx(str, string_utils::OPERATION_PATTERN);
    if (match.empty()) {
        throw std::runtime_error("invalid operation");
    }

    str = str.substr(match.length());
    return match;
}

void Parser::parseWhitespace(std::string &str) {
    std::string match =
        string_utils::getRgx(str, string_utils::WHITESPACE_PATTERN);
    if (match.empty()) {
        throw std::runtime_error("whitespace expected");
    }
    str = str.substr(match.length());
}

unsigned int Parser::parseRegister(std::string &str) {
    std::string match =
        string_utils::getRgx(str, string_utils::REGISTER_PATTERN);
    if (match.empty()) {
        throw std::runtime_error("invalid register");
    }

    str = str.substr(match.length());

    // TODO: add more register variants
    if (match == "zero") {
        return 0;
    } else if (match == "ra") {
        return 1;
    } else if (match == "sp") {
        return 2;
    } else if (match == "gp") {
        return 3;
    } else if (match == "tp") {
        return 4;
    } else if (match == "t0") {
        return 5;
    } else if (match == "t1") {
        return 6;
    } else if (match == "t2") {
        return 7;
    } else if (match == "s0" || match == "fp") {
        return 8;
    } else if (match == "s1") {
        return 9;
    } else if (match == "a0") {
        return 10;
    } else if (match == "a1") {
        return 11;
    } else if (match == "a2") {
        return 12;
    } else if (match == "a3") {
        return 13;
    } else if (match == "a4") {
        return 14;
    } else if (match == "a5") {
        return 15;
    } else if (match == "a6") {
        return 16;
    } else if (match == "a7") {
        return 17;
    } else if (match == "s2") {
        return 18;
    } else if (match == "s3") {
        return 19;
    } else if (match == "s4") {
        return 20;
    } else if (match == "s5") {
        return 21;
    } else if (match == "s6") {
        return 22;
    } else if (match == "s7") {
        return 23;
    } else if (match == "s8") {
        return 24;
    } else if (match == "s9") {
        return 25;
    } else if (match == "s10") {
        return 26;
    } else if (match == "s11") {
        return 27;
    } else if (match == "t3") {
        return 28;
    } else if (match == "t4") {
        return 29;
    } else if (match == "t5") {
        return 30;
    } else if (match == "t6") {
        return 31;
    } else {
        throw std::runtime_error("invalid register");
    }
}

void Parser::parseComma(std::string &str) {
    std::string match = string_utils::getRgx(str, string_utils::COMMA_PATTERN);
    if (match.empty()) {
        throw std::runtime_error("comma expected");
    }
    str = str.substr(match.length());
}

int Parser::parseImm(std::string &str, unsigned int bitSize) {
    std::string match = string_utils::getRgx(str, string_utils::IMM_PATTERN);
    if (match.empty()) {
        throw std::runtime_error("invalid imm");
    }
    str = str.substr(match.length());

    int value = std::stoi(match);
    if (!inRange(value, bitSize)) {
        throw std::runtime_error("imm out of range");
    } else {
        return value;
    }
}

void Parser::parseOpenParen(std::string &str) {
    std::string match =
        string_utils::getRgx(str, string_utils::OPEN_PAREN_PATTERN);
    if (match.empty()) {
        throw std::runtime_error("parenthesis expected");
    }
    str = str.substr(match.length());
}

void Parser::parseCloseParen(std::string &str) {
    std::string match =
        string_utils::getRgx(str, string_utils::CLOSE_PAREN_PATTERN);
    if (match.empty()) {
        throw std::runtime_error("closing parenthesis expected");
    }
    str = str.substr(match.length());
}

inline void printInst(Instruction &_inst) {
    std::cout << _inst.opName << "\nrd: " << _inst.rd << "\nrs1: " << _inst.rs1
              << "\nrs2: " << _inst.rs2 << "\nimm: " << _inst.imm
              << "\noffset: " << _inst.offset << '\n';
}

void Parser::parse() {
    for (unsigned int i = 0; i < this->inputFile.size(); ++i) {
        unsigned int lineNo = i + 1;
        std::string currLabel = parseLabel(this->inputFile[i]);
        if (currLabel != "") {
            this->labelLocations.insert({parseLabelName(currLabel), lineNo});
        }
    }

    std::cout << "LABEL\tLINE NUMBER\n";
    for (const auto &[label, lineno] : labelLocations) {
        std::cout << label << '\t' << lineno << '\n';
    }
    std::cout << '\n';

    for (unsigned int i = 0; i < this->inputFile.size(); ++i) {
        unsigned int lineNo = i + 1;
        std::string tmp_line(this->inputFile[i]);

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
                inst.imm = parseImm(tmp_line, 100);

                printInst(inst);
            } catch (const std::exception &e) {
                std::cout << this->inputFile[i] << '\n';
                std::cerr << e.what() << '\n';
                break;
            }
        } else if (op == "add") {
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
                std::cout << this->inputFile[i] << '\n';
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
                std::cout << this->inputFile[i] << '\n';
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
                std::cout << this->inputFile[i] << '\n';
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
                std::cout << this->inputFile[i] << '\n';
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
                std::cout << this->inputFile[i] << '\n';
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
                std::cout << this->inputFile[i] << '\n';
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
                std::cout << this->inputFile[i] << '\n';
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
                std::cout << this->inputFile[i] << '\n';
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
                std::cout << this->inputFile[i] << '\n';
                std::cerr << e.what() << '\n';
                break;
            }
        } else if (op == "lw") {
            try {
                Instruction inst;
                inst.opName = parseOperation(tmp_line);
                parseWhitespace(tmp_line);
                inst.rd = parseRegister(tmp_line);
                parseComma(tmp_line);
                inst.imm = parseImm(tmp_line, 100);
                parseOpenParen(tmp_line);
                inst.rs1 = parseRegister(tmp_line);
                parseCloseParen(tmp_line);

                printInst(inst);
            } catch (const std::exception &e) {
                std::cout << this->inputFile[i] << '\n';
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
                inst.imm = parseImm(tmp_line, 100);

                printInst(inst);
            } catch (const std::exception &e) {
                std::cout << this->inputFile[i] << '\n';
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
                try {
                    inst.offset = parseImm(tmp_line, 12);
                } catch (const std::exception &_) {
                    std::string labelName = parseLabelName(tmp_line);
                    if (!labelLocations[labelName]) {
                        throw std::runtime_error("invalid label name");
                    }
                    inst.offset = (labelLocations[labelName] - lineNo) * 4;
                }

                if (!tmp_line.empty()) {
                    throw std::runtime_error("expect end of line");
                }

                printInst(inst);
            } catch (const std::exception &e) {
                std::cout << this->inputFile[i] << '\n';
                std::cerr << e.what() << '\n';
                break;
            }
        } else if (op == "sw") {
            try {
                Instruction inst;
                inst.opName = parseOperation(tmp_line);
                parseWhitespace(tmp_line);
                inst.rs2 = parseRegister(tmp_line);
                parseComma(tmp_line);
                inst.imm = parseImm(tmp_line, 100);
                parseOpenParen(tmp_line);
                inst.rs1 = parseRegister(tmp_line);
                parseCloseParen(tmp_line);

                printInst(inst);
            } catch (const std::exception &e) {
                std::cout << this->inputFile[i] << '\n';
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
                try {
                    inst.offset = parseImm(tmp_line, 12);
                } catch (const std::exception &_) {
                    std::string labelName = parseLabelName(tmp_line);
                    if (!labelLocations[labelName]) {
                        throw std::runtime_error("invalid label name");
                    }
                    inst.offset = (labelLocations[labelName] - lineNo) * 4;
                }

                if (!tmp_line.empty()) {
                    throw std::runtime_error("expect end of line");
                }

                printInst(inst);
            } catch (const std::exception &e) {
                std::cout << this->inputFile[i] << '\n';
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
                try {
                    inst.offset = parseImm(tmp_line, 12);
                } catch (const std::exception &_) {
                    std::string labelName = parseLabelName(tmp_line);
                    if (!labelLocations[labelName]) {
                        throw std::runtime_error("invalid label name");
                    }
                    inst.offset = (labelLocations[labelName] - lineNo) * 4;
                }

                if (!tmp_line.empty()) {
                    throw std::runtime_error("expect end of line");
                }

                printInst(inst);
            } catch (const std::exception &e) {
                std::cout << this->inputFile[i] << '\n';
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
                try {
                    inst.offset = parseImm(tmp_line, 12);
                } catch (const std::exception &_) {
                    std::string labelName = parseLabelName(tmp_line);
                    if (!labelLocations[labelName]) {
                        throw std::runtime_error("invalid label name");
                    }
                    inst.offset = (labelLocations[labelName] - lineNo) * 4;
                }

                if (!tmp_line.empty()) {
                    throw std::runtime_error("expect end of line");
                }

                printInst(inst);
            } catch (const std::exception &e) {
                std::cout << this->inputFile[i] << '\n';
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
                try {
                    inst.offset = parseImm(tmp_line, 12);
                } catch (const std::exception &_) {
                    std::string labelName = parseLabelName(tmp_line);
                    if (!labelLocations[labelName]) {
                        throw std::runtime_error("invalid label name");
                    }
                    inst.offset = (labelLocations[labelName] - lineNo) * 4;
                }

                if (!tmp_line.empty()) {
                    throw std::runtime_error("expect end of line");
                }

                printInst(inst);
            } catch (const std::exception &e) {
                std::cout << this->inputFile[i] << '\n';
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
                try {
                    inst.offset = parseImm(tmp_line, 12);
                } catch (const std::exception &_) {
                    std::string labelName = parseLabelName(tmp_line);
                    if (!labelLocations[labelName]) {
                        throw std::runtime_error("invalid label name");
                    }
                    inst.offset = (labelLocations[labelName] - lineNo) * 4;
                }

                if (!tmp_line.empty()) {
                    throw std::runtime_error("expect end of line");
                }

                printInst(inst);
            } catch (const std::exception &e) {
                std::cout << this->inputFile[i] << '\n';
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
                try {
                    inst.offset = parseImm(tmp_line, 12);
                } catch (const std::exception &_) {
                    std::string labelName = parseLabelName(tmp_line);
                    if (!labelLocations[labelName]) {
                        throw std::runtime_error("invalid label name");
                    }
                    inst.offset = (labelLocations[labelName] - lineNo) * 4;
                }

                if (!tmp_line.empty()) {
                    throw std::runtime_error("expect end of line");
                }

                printInst(inst);
            } catch (const std::exception &e) {
                std::cout << this->inputFile[i] << '\n';
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
                inst.imm = parseImm(tmp_line, 100);

                printInst(inst);
            } catch (const std::exception &e) {
                std::cout << this->inputFile[i] << '\n';
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
                inst.imm = parseImm(tmp_line, 100);

                printInst(inst);
            } catch (const std::exception &e) {
                std::cout << this->inputFile[i] << '\n';
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
                try {
                    inst.offset = parseImm(tmp_line, 12);
                } catch (const std::exception &_) {
                    std::string labelName = parseLabelName(tmp_line);
                    if (!labelLocations[labelName]) {
                        throw std::runtime_error("invalid label name");
                    }
                    inst.offset = (labelLocations[labelName] - lineNo) * 4;
                }

                if (!tmp_line.empty()) {
                    throw std::runtime_error("expect end of line");
                }

                printInst(inst);
            } catch (const std::exception &e) {
                std::cout << this->inputFile[i] << '\n';
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
                std::cout << this->inputFile[i] << '\n';
                std::cerr << e.what() << '\n';
                break;
            }
        } else if (op == "rst") {
            try {
                Instruction inst;
                inst.opName = parseOperation(tmp_line);

                printInst(inst);
            } catch (const std::exception &e) {
                std::cout << this->inputFile[i] << '\n';
                std::cerr << e.what() << '\n';
                break;
            }
        } else if (op == "halt") {
            try {
                Instruction inst;
                inst.opName = parseOperation(tmp_line);

                printInst(inst);
            } catch (const std::exception &e) {
                std::cout << this->inputFile[i] << '\n';
                std::cerr << e.what() << '\n';
                break;
            }
        } else if (op == "rvrs") {
            try {
                Instruction inst;
                inst.opName = parseOperation(tmp_line);
                parseWhitespace(tmp_line);
                inst.rd = parseRegister(tmp_line);
                parseComma(tmp_line);
                inst.rs1 = parseRegister(tmp_line);

                printInst(inst);
            } catch (const std::exception &e) {
                std::cout << this->inputFile[i] << '\n';
                std::cerr << e.what() << '\n';
                break;
            }
        } else {
            // parseError("invalid operation");
            std::cerr << '\n' << this->inputFile[i] << "\ninvalid operation\n";
            break;
        }
        std::cout << '\n';
    }
}
