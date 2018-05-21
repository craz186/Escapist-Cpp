//
// Created by Sean on 13/05/2018.
//

#include <fstream>
#include "Utils.h"

vector<string> Utils::split(const string &text, char sep) {
    vector<string> tokens;
    size_t start = 0, end = 0;
    while ((end = text.find(sep, start)) != string::npos) {
        tokens.push_back(text.substr(start, end - start));
        start = end + 1;
    }
    tokens.push_back(text.substr(start));
    return tokens;
}

int Utils::getNumberOfLinesInFile(string filePath) {
    int number_of_lines = 0;
    std::string line;
    std::ifstream file(filePath);

    while (std::getline(file, line))
        ++number_of_lines;

    file.close();
    return number_of_lines;
}
