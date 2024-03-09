#include "parser.h"
#include <fstream>
#include <iostream>

int main(int argc, char **argv) {
    if (argc < 2) {
        std::cout << "Missing arguments!!!\n\n";
        std::cout << "Usage:\n";
        std::cout << "./a.out <path/to/src/file>\n";
        return -1;
    }

    std::ifstream inputFile(argv[1]);
    if (!inputFile.is_open()) {
        std::cout << "File is non-existant\n";
        return 69;
    }

    Parser parser(inputFile);
    parser.parse();

    std::ofstream outputFile("out.txt");
    for (auto line : parser.inputFile) {
        outputFile << line << '\n';
    }

    // std::cout << "Content is written to out.txt\n";
    outputFile.close();

    return 0;
}
