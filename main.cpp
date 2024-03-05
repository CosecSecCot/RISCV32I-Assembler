#include <fstream>
#include <iostream>
using namespace std;

int main(int argc, char **argv) {
    ifstream input_file(argv[1]);
    if (!input_file.is_open()) {
        cout << "File is non-existant\n";
        return -1;
    }

    vector<string> lines;
    while (!input_file.eof()) {
        string line;
        getline(input_file, line);
        lines.push_back(line);
    }

    ofstream output_file("out.txt");
    for (auto line : lines) {
        output_file << line << '\n';
    }

    cout << "Content is written to out.txt\n";
    output_file.close();

    return 0;
}
