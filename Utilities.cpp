//
// Created by bibhash on 9/14/19.
//

#include "Utilities.hpp"

std::string Utils::trim(std::string &word) {
    std::string whitespace = " \t";
    auto strBegin = word.find_first_not_of(whitespace);
    if (strBegin == std::string::npos) {
        return "";
    }
    auto strEnd = word.size();
    auto strRange = strEnd - strBegin + 1;
    return word.substr(strBegin, strRange);
}

std::string Utils::toLowerCase(std::string &word) {
    std::string temp;

    for (char c : word) {
        temp.push_back(tolower(c));
    }

    return temp;
}

std::string Utils::getValue(std::string &line) {
    auto pos = line.find(':');
    std::string value = line.substr(pos+1);
    return value;
}

Cards Utils::toCards(string a_card) {
    string t_face = a_card.substr(0, a_card.length()-1);
    string t_suite = a_card.substr(a_card.length()-1);
    Cards temp(t_face, t_suite);
    return temp;
}