#include <fstream>
#include <iostream>
#include <regex>
#include <string_utils.h>

int main(int argc, char **argv) {
    std::ifstream inputFile(argv[1]);
    if (!inputFile.is_open()) {
        std::cout << "File is non-existant\n";
        return 69;
    }

    std::vector<std::string> lines;
    while (!inputFile.eof()) {
        std::string line;
        getline(inputFile, line);

        std::string trimmedLine = string_utils::trim(line);
        if (trimmedLine != "") {
            std::cout << line << '\n';
            lines.push_back(trimmedLine);
        }
    }

    std::ofstream outputFile("out.txt");
    for (auto line : lines) {
        outputFile << line << '\n';
    }

    std::cout << "Content is written to out.txt\n";
    outputFile.close();

    return 0;
}
