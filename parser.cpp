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

std::string Parser::parseRTypeInst(std::string opName, unsigned int rd,
                                   unsigned int rs1, unsigned int rs2) {
    std::string output = "";
    if (opName == "add") {
        output = "0110011";
        output = " " + output;
        output = std::bitset<5>(rd).to_string() + output;
        output = " " + output;
        output = "000" + output;
        output = " " + output;
        output = std::bitset<5>(rs1).to_string() + output;
        output = " " + output;
        output = std::bitset<5>(rs1).to_string() + output;
        output = " " + output;
        output = "0000000" + output;
    } else if (opName == "sub") {
        output = "0110011";
        output = " " + output;
        output = std::bitset<5>(rd).to_string() + output;
        output = " " + output;
        output = "000" + output;
        output = " " + output;
        output = std::bitset<5>(rs1).to_string() + output;
        output = " " + output;
        output = std::bitset<5>(rs1).to_string() + output;
        output = " " + output;
        output = "0100000" + output;
    } else if (opName == "sll") {
        output = "0110011";
        output = " " + output;
        output = std::bitset<5>(rd).to_string() + output;
        output = " " + output;
        output = "001" + output;
        output = " " + output;
        output = std::bitset<5>(rs1).to_string() + output;
        output = " " + output;
        output = std::bitset<5>(rs1).to_string() + output;
        output = " " + output;
        output = "0000000" + output;
    } else if (opName == "slt") {
        output = "0110011";
        output = " " + output;
        output = std::bitset<5>(rd).to_string() + output;
        output = " " + output;
        output = "010" + output;
        output = " " + output;
        output = std::bitset<5>(rs1).to_string() + output;
        output = " " + output;
        output = std::bitset<5>(rs1).to_string() + output;
        output = " " + output;
        output = "0000000" + output;
    } else if (opName == "sltu") {
        output = "0110011";
        output = " " + output;
        output = std::bitset<5>(rd).to_string() + output;
        output = " " + output;
        output = "011" + output;
        output = " " + output;
        output = std::bitset<5>(rs1).to_string() + output;
        output = " " + output;
        output = std::bitset<5>(rs1).to_string() + output;
        output = " " + output;
        output = "0000000" + output;
    } else if (opName == "xor") {
        output = "0110011";
        output = " " + output;
        output = std::bitset<5>(rd).to_string() + output;
        output = " " + output;
        output = "100" + output;
        output = " " + output;
        output = std::bitset<5>(rs1).to_string() + output;
        output = " " + output;
        output = std::bitset<5>(rs1).to_string() + output;
        output = " " + output;
        output = "0000000" + output;
    } else if (opName == "srl") {
        output = "0110011";
        output = " " + output;
        output = std::bitset<5>(rd).to_string() + output;
        output = " " + output;
        output = "101" + output;
        output = " " + output;
        output = std::bitset<5>(rs1).to_string() + output;
        output = " " + output;
        output = std::bitset<5>(rs1).to_string() + output;
        output = " " + output;
        output = "0000000" + output;
    } else if (opName == "or") {
        output = "0110011";
        output = " " + output;
        output = std::bitset<5>(rd).to_string() + output;
        output = " " + output;
        output = "110" + output;
        output = " " + output;
        output = std::bitset<5>(rs1).to_string() + output;
        output = " " + output;
        output = std::bitset<5>(rs1).to_string() + output;
        output = " " + output;
        output = "0000000" + output;
    } else if (opName == "and") {
        output = "0110011";
        output = " " + output;
        output = std::bitset<5>(rd).to_string() + output;
        output = " " + output;
        output = "111" + output;
        output = " " + output;
        output = std::bitset<5>(rs1).to_string() + output;
        output = " " + output;
        output = std::bitset<5>(rs1).to_string() + output;
        output = " " + output;
        output = "0000000" + output;
    }

    std::cout << "R Type Binary output: ";
    std::cout << output;
    return output;
}

std::string Parser::parseITypeInst(std::string opName, unsigned int rd,
                                   unsigned int rs1, unsigned int imm) {
    std::string output = "";
    if (opName == "addi") {
        output = "0010011";
        output = " " + output;
        output = std::bitset<5>(rd).to_string() + output;
        output = " " + output;
        output = "000" + output;
        output = " " + output;
        output = std::bitset<5>(rs1).to_string() + output;
        output = " " + output;
        std::string im = std::bitset<12>(imm).to_string();
        std::string slicedImm = string_utils::reverseSlice(im, 11, 0);
        output = slicedImm + output;
    } else if (opName == "lw") {
        output = "0000011";
        output = " " + output;
        output = std::bitset<5>(rd).to_string() + output;
        output = " " + output;
        output = "010" + output;
        output = " " + output;
        output = std::bitset<5>(rs1).to_string() + output;
        output = " " + output;
        std::string im = std::bitset<12>(imm).to_string();
        std::string slicedImm = string_utils::reverseSlice(im, 11, 0);
        output = slicedImm + output;
    } else if (opName == "sltiu") {
        output = "0010011";
        output = " " + output;
        output = std::bitset<5>(rd).to_string() + output;
        output = " " + output;
        output = "011" + output;
        output = " " + output;
        output = std::bitset<5>(rs1).to_string() + output;
        output = " " + output;
        std::string im = std::bitset<12>(imm).to_string();
        std::string slicedImm = string_utils::reverseSlice(im, 11, 0);
        output = slicedImm + output;
    } else if (opName == "jalr") {
        output = "1100111";
        output = " " + output;
        output = std::bitset<5>(rd).to_string() + output;
        output = " " + output;
        output = "000" + output;
        output = " " + output;
        output = std::bitset<5>(rs1).to_string() + output;
        output = " " + output;
        std::string im = std::bitset<12>(imm).to_string();
        std::string slicedImm = string_utils::reverseSlice(im, 11, 0);
        output = slicedImm + output;
    }

    std::cout << "I Type Binary output: ";
    std::cout << output;
    return output;
}

std::string parseSTypeInst(std::string opName, unsigned int rs1,
                           unsigned int rs2, unsigned int imm) {
    std::string output = "";
    if (opName == "sw") {
        output = "0100011";
        output = " " + output;
        std::string im = std::bitset<12>(imm).to_string() + output;
        std::string slicedImm = string_utils::reverseSlice(im, 4, 0);
        output = slicedImm + output;
        output = "010" + output;
        output = std::bitset<5>(rs1).to_string() + output;
        output = " " + output;
        output = std::bitset<5>(rs2).to_string() + output;
        output = " " + output;
        slicedImm = string_utils::reverseSlice(im, 11, 5);
        output = slicedImm + output;
    }

    std::cout << "S Type Binary output: ";
    std::cout << output;
    return output;
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
                std::string opName = parseOperation(tmp_line);
                parseWhitespace(tmp_line);
                unsigned int rd = parseRegister(tmp_line);
                parseComma(tmp_line);
                unsigned int rs1 = parseRegister(tmp_line);
                parseComma(tmp_line);
                int imm = parseImm(tmp_line, 100);

                std::string outputBinary = parseITypeInst(opName, rd, rs1, imm);
            } catch (const std::exception &e) {
                std::cout << this->inputFile[i] << '\n';
                std::cerr << e.what() << '\n';
                break;
            }
        } else if (op == "add") {
            try {
                std::string opName = parseOperation(tmp_line);
                parseWhitespace(tmp_line);
                unsigned int rd = parseRegister(tmp_line);
                parseComma(tmp_line);
                unsigned int rs1 = parseRegister(tmp_line);
                parseComma(tmp_line);
                unsigned int rs2 = parseRegister(tmp_line);

                std::string outputBinary = parseRTypeInst(opName, rd, rs1, rs2);
            } catch (const std::exception &e) {
                std::cout << this->inputFile[i] << '\n';
                std::cerr << e.what() << '\n';
                break;
            }
        } else if (op == "sub") {
            try {
                std::string opName = parseOperation(tmp_line);
                parseWhitespace(tmp_line);
                unsigned int rd = parseRegister(tmp_line);
                parseComma(tmp_line);
                unsigned int rs1 = parseRegister(tmp_line);
                parseComma(tmp_line);
                unsigned int rs2 = parseRegister(tmp_line);

                std::string outputBinary = parseRTypeInst(opName, rd, rs1, rs2);
            } catch (const std::exception &e) {
                std::cout << this->inputFile[i] << '\n';
                std::cerr << e.what() << '\n';
                break;
            }
        } else if (op == "slt") {
            try {
                std::string opName = parseOperation(tmp_line);
                parseWhitespace(tmp_line);
                unsigned int rd = parseRegister(tmp_line);
                parseComma(tmp_line);
                unsigned int rs1 = parseRegister(tmp_line);
                parseComma(tmp_line);
                unsigned int rs2 = parseRegister(tmp_line);

                std::string outputBinary = parseRTypeInst(opName, rd, rs1, rs2);
            } catch (const std::exception &e) {
                std::cout << this->inputFile[i] << '\n';
                std::cerr << e.what() << '\n';
                break;
            }
        } else if (op == "sltu") {
            try {
                std::string opName = parseOperation(tmp_line);
                parseWhitespace(tmp_line);
                unsigned int rd = parseRegister(tmp_line);
                parseComma(tmp_line);
                unsigned int rs1 = parseRegister(tmp_line);
                parseComma(tmp_line);
                unsigned int rs2 = parseRegister(tmp_line);

                std::string outputBinary = parseRTypeInst(opName, rd, rs1, rs2);
            } catch (const std::exception &e) {
                std::cout << this->inputFile[i] << '\n';
                std::cerr << e.what() << '\n';
                break;
            }
        } else if (op == "xor") {
            try {
                std::string opName = parseOperation(tmp_line);
                parseWhitespace(tmp_line);
                unsigned int rd = parseRegister(tmp_line);
                parseComma(tmp_line);
                unsigned int rs1 = parseRegister(tmp_line);
                parseComma(tmp_line);
                unsigned int rs2 = parseRegister(tmp_line);

                std::string outputBinary = parseRTypeInst(opName, rd, rs1, rs2);
            } catch (const std::exception &e) {
                std::cout << this->inputFile[i] << '\n';
                std::cerr << e.what() << '\n';
                break;
            }
        } else if (op == "sll") {
            try {
                std::string opName = parseOperation(tmp_line);
                parseWhitespace(tmp_line);
                unsigned int rd = parseRegister(tmp_line);
                parseComma(tmp_line);
                unsigned int rs1 = parseRegister(tmp_line);
                parseComma(tmp_line);
                unsigned int rs2 = parseRegister(tmp_line);

                std::string outputBinary = parseRTypeInst(opName, rd, rs1, rs2);
            } catch (const std::exception &e) {
                std::cout << this->inputFile[i] << '\n';
                std::cerr << e.what() << '\n';
                break;
            }
        } else if (op == "srl") {
            try {
                std::string opName = parseOperation(tmp_line);
                parseWhitespace(tmp_line);
                unsigned int rd = parseRegister(tmp_line);
                parseComma(tmp_line);
                unsigned int rs1 = parseRegister(tmp_line);
                parseComma(tmp_line);
                unsigned int rs2 = parseRegister(tmp_line);

                std::string outputBinary = parseRTypeInst(opName, rd, rs1, rs2);
            } catch (const std::exception &e) {
                std::cout << this->inputFile[i] << '\n';
                std::cerr << e.what() << '\n';
                break;
            }
        } else if (op == "or") {
            try {
                std::string opName = parseOperation(tmp_line);
                parseWhitespace(tmp_line);
                unsigned int rd = parseRegister(tmp_line);
                parseComma(tmp_line);
                unsigned int rs1 = parseRegister(tmp_line);
                parseComma(tmp_line);
                unsigned int rs2 = parseRegister(tmp_line);

                std::string outputBinary = parseRTypeInst(opName, rd, rs1, rs2);
            } catch (const std::exception &e) {
                std::cout << this->inputFile[i] << '\n';
                std::cerr << e.what() << '\n';
                break;
            }
        } else if (op == "and") {
            try {
                std::string opName = parseOperation(tmp_line);
                parseWhitespace(tmp_line);
                unsigned int rd = parseRegister(tmp_line);
                parseComma(tmp_line);
                unsigned int rs1 = parseRegister(tmp_line);
                parseComma(tmp_line);
                unsigned int rs2 = parseRegister(tmp_line);

                std::string outputBinary = parseRTypeInst(opName, rd, rs1, rs2);
            } catch (const std::exception &e) {
                std::cout << this->inputFile[i] << '\n';
                std::cerr << e.what() << '\n';
                break;
            }
        } else if (op == "lw") {
            try {
                std::string opName = parseOperation(tmp_line);
                parseWhitespace(tmp_line);
                unsigned int rd = parseRegister(tmp_line);
                parseComma(tmp_line);
                int imm = parseImm(tmp_line, 100);
                parseOpenParen(tmp_line);
                unsigned int rs1 = parseRegister(tmp_line);
                parseCloseParen(tmp_line);

                std::string outputBinary = parseITypeInst(opName, rd, rs1, imm);
            } catch (const std::exception &e) {
                std::cout << this->inputFile[i] << '\n';
                std::cerr << e.what() << '\n';
                break;
            }
        } else if (op == "sltiu") {
            try {
                std::string opName = parseOperation(tmp_line);
                parseWhitespace(tmp_line);
                unsigned int rd = parseRegister(tmp_line);
                parseComma(tmp_line);
                unsigned int rs1 = parseRegister(tmp_line);
                parseComma(tmp_line);
                int imm = parseImm(tmp_line, 100);

                std::string outputBinary = parseITypeInst(opName, rd, rs1, imm);
            } catch (const std::exception &e) {
                std::cout << this->inputFile[i] << '\n';
                std::cerr << e.what() << '\n';
                break;
            }
        } else if (op == "jalr") {
            try {
                std::string opName = parseOperation(tmp_line);
                parseWhitespace(tmp_line);
                unsigned int rd = parseRegister(tmp_line);
                parseComma(tmp_line);
                unsigned int rs1 = parseRegister(tmp_line);
                parseComma(tmp_line);
                int offset;
                try {
                    offset = parseImm(tmp_line, 12);
                } catch (const std::exception &_) {
                    std::string labelName = parseLabelName(tmp_line);
                    if (!labelLocations[labelName]) {
                        throw std::runtime_error("invalid label name");
                    }
                    offset = (labelLocations[labelName] - lineNo) * 4;
                }

                if (!tmp_line.empty()) {
                    throw std::runtime_error("expect end of line");
                }

                std::string outputBinary =
                    parseITypeInst(opName, rd, rs1, offset);
            } catch (const std::exception &e) {
                std::cout << this->inputFile[i] << '\n';
                std::cerr << e.what() << '\n';
                break;
            }
        } else if (op == "sw") {
            try {
                std::string opName = parseOperation(tmp_line);
                parseWhitespace(tmp_line);
                unsigned int rs2 = parseRegister(tmp_line);
                parseComma(tmp_line);
                int imm = parseImm(tmp_line, 100);
                parseOpenParen(tmp_line);
                unsigned int rs1 = parseRegister(tmp_line);
                parseCloseParen(tmp_line);

                // printInst(inst);
            } catch (const std::exception &e) {
                std::cout << this->inputFile[i] << '\n';
                std::cerr << e.what() << '\n';
                break;
            }
        } else if (op == "beq") {
            try {
                std::string opName = parseOperation(tmp_line);
                parseWhitespace(tmp_line);
                unsigned int rs1 = parseRegister(tmp_line);
                parseComma(tmp_line);
                unsigned int rs2 = parseRegister(tmp_line);
                parseComma(tmp_line);
                try {
                    int offset = parseImm(tmp_line, 12);
                } catch (const std::exception &_) {
                    std::string labelName = parseLabelName(tmp_line);
                    if (!labelLocations[labelName]) {
                        throw std::runtime_error("invalid label name");
                    }
                    int offset = (labelLocations[labelName] - lineNo) * 4;
                }

                if (!tmp_line.empty()) {
                    throw std::runtime_error("expect end of line");
                }

                // printInst(inst);
            } catch (const std::exception &e) {
                std::cout << this->inputFile[i] << '\n';
                std::cerr << e.what() << '\n';
                break;
            }
        } else if (op == "bne") {
            try {
                std::string opName = parseOperation(tmp_line);
                parseWhitespace(tmp_line);
                unsigned int rs1 = parseRegister(tmp_line);
                parseComma(tmp_line);
                unsigned int rs2 = parseRegister(tmp_line);
                parseComma(tmp_line);
                try {
                    int offset = parseImm(tmp_line, 12);
                } catch (const std::exception &_) {
                    std::string labelName = parseLabelName(tmp_line);
                    if (!labelLocations[labelName]) {
                        throw std::runtime_error("invalid label name");
                    }
                    int offset = (labelLocations[labelName] - lineNo) * 4;
                }

                if (!tmp_line.empty()) {
                    throw std::runtime_error("expect end of line");
                }

                // printInst(inst);
            } catch (const std::exception &e) {
                std::cout << this->inputFile[i] << '\n';
                std::cerr << e.what() << '\n';
                break;
            }
        } else if (op == "bge") {
            try {
                std::string opName = parseOperation(tmp_line);
                parseWhitespace(tmp_line);
                unsigned int rs1 = parseRegister(tmp_line);
                parseComma(tmp_line);
                unsigned int rs2 = parseRegister(tmp_line);
                parseComma(tmp_line);
                try {
                    int offset = parseImm(tmp_line, 12);
                } catch (const std::exception &_) {
                    std::string labelName = parseLabelName(tmp_line);
                    if (!labelLocations[labelName]) {
                        throw std::runtime_error("invalid label name");
                    }
                    int offset = (labelLocations[labelName] - lineNo) * 4;
                }

                if (!tmp_line.empty()) {
                    throw std::runtime_error("expect end of line");
                }

                // printInst(inst);
            } catch (const std::exception &e) {
                std::cout << this->inputFile[i] << '\n';
                std::cerr << e.what() << '\n';
                break;
            }
        } else if (op == "bgeu") {
            try {
                std::string opName = parseOperation(tmp_line);
                parseWhitespace(tmp_line);
                unsigned int rs1 = parseRegister(tmp_line);
                parseComma(tmp_line);
                unsigned int rs2 = parseRegister(tmp_line);
                parseComma(tmp_line);
                try {
                    int offset = parseImm(tmp_line, 12);
                } catch (const std::exception &_) {
                    std::string labelName = parseLabelName(tmp_line);
                    if (!labelLocations[labelName]) {
                        throw std::runtime_error("invalid label name");
                    }
                    int offset = (labelLocations[labelName] - lineNo) * 4;
                }

                if (!tmp_line.empty()) {
                    throw std::runtime_error("expect end of line");
                }

                // printInst(inst);
            } catch (const std::exception &e) {
                std::cout << this->inputFile[i] << '\n';
                std::cerr << e.what() << '\n';
                break;
            }
        } else if (op == "blt") {
            try {
                std::string opName = parseOperation(tmp_line);
                parseWhitespace(tmp_line);
                unsigned int rs1 = parseRegister(tmp_line);
                parseComma(tmp_line);
                unsigned int rs2 = parseRegister(tmp_line);
                parseComma(tmp_line);
                try {
                    int offset = parseImm(tmp_line, 12);
                } catch (const std::exception &_) {
                    std::string labelName = parseLabelName(tmp_line);
                    if (!labelLocations[labelName]) {
                        throw std::runtime_error("invalid label name");
                    }
                    int offset = (labelLocations[labelName] - lineNo) * 4;
                }

                if (!tmp_line.empty()) {
                    throw std::runtime_error("expect end of line");
                }

                // printInst(inst);
            } catch (const std::exception &e) {
                std::cout << this->inputFile[i] << '\n';
                std::cerr << e.what() << '\n';
                break;
            }
        } else if (op == "bltu") {
            try {
                std::string opName = parseOperation(tmp_line);
                parseWhitespace(tmp_line);
                unsigned int rs1 = parseRegister(tmp_line);
                parseComma(tmp_line);
                unsigned int rs2 = parseRegister(tmp_line);
                parseComma(tmp_line);
                try {
                    int offset = parseImm(tmp_line, 12);
                } catch (const std::exception &_) {
                    std::string labelName = parseLabelName(tmp_line);
                    if (!labelLocations[labelName]) {
                        throw std::runtime_error("invalid label name");
                    }
                    int offset = (labelLocations[labelName] - lineNo) * 4;
                }

                if (!tmp_line.empty()) {
                    throw std::runtime_error("expect end of line");
                }

                // printInst(inst);
            } catch (const std::exception &e) {
                std::cout << this->inputFile[i] << '\n';
                std::cerr << e.what() << '\n';
                break;
            }
        } else if (op == "auipc") {
            try {
                std::string opName = parseOperation(tmp_line);
                parseWhitespace(tmp_line);
                unsigned int rd = parseRegister(tmp_line);
                parseComma(tmp_line);
                int imm = parseImm(tmp_line, 100);

                // printInst(inst);
            } catch (const std::exception &e) {
                std::cout << this->inputFile[i] << '\n';
                std::cerr << e.what() << '\n';
                break;
            }
        } else if (op == "lui") {
            try {
                std::string opName = parseOperation(tmp_line);
                parseWhitespace(tmp_line);
                unsigned int rd = parseRegister(tmp_line);
                parseComma(tmp_line);
                int imm = parseImm(tmp_line, 100);

                // printInst(inst);
            } catch (const std::exception &e) {
                std::cout << this->inputFile[i] << '\n';
                std::cerr << e.what() << '\n';
                break;
            }
        } else if (op == "jal") {
            try {
                std::string opName = parseOperation(tmp_line);
                parseWhitespace(tmp_line);
                unsigned int rd = parseRegister(tmp_line);
                parseComma(tmp_line);
                try {
                    int offset = parseImm(tmp_line, 12);
                } catch (const std::exception) {
                    std::string labelName = parseLabelName(tmp_line);
                    if (!labelLocations[labelName]) {
                        throw std::runtime_error("invalid label name");
                    }
                    int offset = (labelLocations[labelName] - lineNo) * 4;
                }

                try {
                    parseOpenParen(tmp_line);
                    parseRegister(tmp_line);
                    parseCloseParen(tmp_line);
                } catch (const std::exception) {
                    // do nothing
                }

                if (!tmp_line.empty()) {
                    throw std::runtime_error("expect end of line");
                }

                // printInst(inst);
            } catch (const std::exception &e) {
                std::cout << this->inputFile[i] << '\n';
                std::cerr << e.what() << '\n';
                break;
            }
        } else if (op == "mul") {
            try {
                std::string opName = parseOperation(tmp_line);
                parseWhitespace(tmp_line);
                unsigned int rd = parseRegister(tmp_line);
                parseComma(tmp_line);
                unsigned int rs1 = parseRegister(tmp_line);
                parseComma(tmp_line);
                unsigned int rs2 = parseRegister(tmp_line);

                // printInst(inst);
            } catch (const std::exception &e) {
                std::cout << this->inputFile[i] << '\n';
                std::cerr << e.what() << '\n';
                break;
            }
        } else if (op == "rst") {
            try {
                std::string opName = parseOperation(tmp_line);

                // printInst(inst);
            } catch (const std::exception &e) {
                std::cout << this->inputFile[i] << '\n';
                std::cerr << e.what() << '\n';
                break;
            }
        } else if (op == "halt") {
            try {
                std::string opName = parseOperation(tmp_line);

                // printInst(inst);
            } catch (const std::exception &e) {
                std::cout << this->inputFile[i] << '\n';
                std::cerr << e.what() << '\n';
                break;
            }
        } else if (op == "rvrs") {
            try {
                std::string opName = parseOperation(tmp_line);
                parseWhitespace(tmp_line);
                unsigned int rd = parseRegister(tmp_line);
                parseComma(tmp_line);
                unsigned int rs1 = parseRegister(tmp_line);

                // printInst(inst);
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
