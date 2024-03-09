#include <iostream>
#include <parser.h>

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
