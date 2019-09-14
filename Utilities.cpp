//
// Created by bibhash on 9/14/19.
//

#include "Utilities.hpp"

std::string Utilities::trim(std::string &word) {
    std::string whitespace = " \t";
    auto strBegin = word.find_first_not_of(whitespace);
    if (strBegin == std::string::npos) {
        return "";
    }
    auto strEnd = word.size();
    auto strRange = strEnd - strBegin + 1;
    return word.substr(strBegin, strRange);
}

std::string Utilities::toLowerCase(std::string &word) {
    std::string temp;

    for (char c : word) {
        temp.push_back(tolower(c));
    }

    return temp;
}

std::string Utilities::getValue(std::string &line) {
    auto pos = line.find(':');
    std::string value = line.substr(pos+1);
    return value;
}