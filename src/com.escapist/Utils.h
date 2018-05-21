//
// Created by Sean on 13/05/2018.
//

#ifndef ESCAPIST_UTILS_H
#define ESCAPIST_UTILS_H

#include <vector>
#include <string>

using namespace std;

class Utils {

public:
    static vector<string> split(const std::string &text, char sep);

    static int getNumberOfLinesInFile(string file);
};

#endif //ESCAPIST_UTILS_H
