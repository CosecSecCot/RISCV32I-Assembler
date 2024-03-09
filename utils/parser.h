#ifndef _PARSER_H
#define _PARSER_H

#include <fstream>
#include <iostream>
#include <string>
#include <string_utils.h>
#include <vector>

class Parser {
public:
    std::vector<std::string> inputFile;

    Parser(std::ifstream &inputFileStream) {
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
};

#endif
