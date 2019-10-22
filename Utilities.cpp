/*
 ************************************************************
 * Name: Bibhash Mulmi                                      *
 * Project: P1 Five Crowns CPP                              *
 * Class: OPL Fall 19                                       *
 * Date: 10/23/2019                                         *
 ************************************************************
*/

// Created by bibhash on 9/14/19.


#include "Utilities.hpp"

/**********************************************************************
 * Function Name:
 * Purpose:
 * Parameters:
 *
 * Return Value:
 * Local Variables:
 *
 * Algorithm:
 *               1)
 * Assistance Received: None
 **********************************************************************/
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

/**********************************************************************
 * Function Name:
 * Purpose:
 * Parameters:
 *
 * Return Value:
 * Local Variables:
 *
 * Algorithm:
 *               1)
 * Assistance Received: None
 **********************************************************************/
std::string Utils::toLowerCase(std::string &word) {
    std::string temp;

    for (char c : word) {
        temp.push_back(tolower(c));
    }

    return temp;
}

/**********************************************************************
 * Function Name:
 * Purpose:
 * Parameters:
 *
 * Return Value:
 * Local Variables:
 *
 * Algorithm:
 *               1)
 * Assistance Received: None
 **********************************************************************/
std::string Utils::getValue(std::string &line) {
    auto pos = line.find(':');
    std::string value = line.substr(pos+1);
    return value;
}

/**********************************************************************
 * Function Name:
 * Purpose:
 * Parameters:
 *
 * Return Value:
 * Local Variables:
 *
 * Algorithm:
 *               1)
 * Assistance Received: None
 **********************************************************************/
Cards Utils::toCards(string a_card) {
    string t_face = a_card.substr(0, a_card.length()-1);
    string t_suite = a_card.substr(a_card.length()-1);
    Cards temp(t_face, t_suite);
    return temp;
}
