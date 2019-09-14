//
// Created by bibhash on 9/12/19.
//
#ifndef UTILITIES_HPP
#define UTILITIES_HPP

#include <iostream>

using namespace std;

string toLowerCase(string str) {
    string temp;

    for (char c : str) {
        temp.push_back(tolower(c));
    }

    return temp;
}

string getValue(string line) {
    auto pos = line.find(':');
    string value = line.substr(pos+1);
    return value;
}

#endif //FIVE_CROWNS_CPP_UTILITIES_HPP
