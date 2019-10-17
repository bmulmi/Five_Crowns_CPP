//
// Created by bibhash on 9/14/19.
//

#ifndef FIVE_CROWNS_CPP_UTILITIES_HPP
#define FIVE_CROWNS_CPP_UTILITIES_HPP


#include <string>
#include "Cards.hpp"

namespace Utils {
    std::string toLowerCase(std::string &word);
    std::string getValue(std::string &line);
    std::string trim(std::string &word);
    Cards toCards(string a_card);
}

#endif //FIVE_CROWNS_CPP_UTILITIES_HPP
