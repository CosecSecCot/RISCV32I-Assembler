#include "parser.h"
#include <fstream>
#include <iostream>

int main(int argc, char **argv) {
    if (argc < 2 || argc > 3) {
        std::cerr << "Missing arguments!!!\n\n";
        std::cerr << "Usage:\n";
        std::cerr
            << "./path/to/a.out <path/to/input/file> <path/to/output/file><\n";
        return -1;
    }

    std::ifstream inputFile(argv[1]);
    if (!inputFile.is_open()) {
        std::cerr << "File doesn't exist\n";
        return 69;
    }

    Parser parser(inputFile);
    try {
        parser.parse();
    } catch (const std::exception &e) {
        std::cerr << e.what() << '\n';
        return -1;
    }

    std::string outputFileName;
    if (argc == 3) {
        outputFileName = argv[2];
    } else {
        outputFileName = "out.txt";
    }
    std::ofstream outputFile(outputFileName);
    for (auto line : parser.outputFileContent) {
        outputFile << line;
    }

    std::cout << "output is written to " << outputFileName << '\n';
    outputFile.close();

    return 0;
}
