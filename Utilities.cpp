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
 * Function Name: trim
 * Purpose: To remove the leading white spaces from a string
 * Parameters:
 *          word, a string value passed by reference. The white spaces of
 *          this string will be removed.
 * Return Value: a string value
 * Local Variables:
 *          strBegin, an int value that stores the index of first non-white
 *          space character in a string
 *
 *          strEnd, an int value that holds the size of the string
 *
 *          strRange, an int value that holds the size of string after
 *          removing white space.
 * Algorithm:
 *               1) Get first non white space character index
 *               2) Check if the string is empty, return if true.
 *               3) Get the total size of string
 *               4) Get the size of word excluding the leading white space
 *                  characters
 *               5) Only return the sub string from strBegin to strRange
 * Assistance Received: Stack Overflow
 * https://stackoverflow.com/questions/1798112/removing-leading-and-trailing-spaces-from-a-string
 **********************************************************************/
std::string Utils::trim(std::string &word) {
    std::string whitespace = " \t";
    auto strBegin = word.find_first_not_of(whitespace);
    // when the string is empty
    if (strBegin == std::string::npos) {
        return "";
    }
    auto strEnd = word.size();
    auto strRange = strEnd - strBegin + 1;
    return word.substr(strBegin, strRange);
}

/**********************************************************************
 * Function Name: toLowerCase
 * Purpose: To convert the string to lower case
 * Parameters:
 *          word, a string value passed by reference.
 * Return Value: a string value
 * Local Variables:
 *          temp, a string value. It holds the lower case converted string.
 * Algorithm:
 *               1) For each character in string, convert them to lower case
 *                  and add it to temp vector.
 *               2) Return the temp vector.
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
 * Function Name: getValue
 * Purpose: To get the value of a parameter from the serialized file.
 * Parameters:
 *          line, a string value. It holds the line from serialized file.
 * Return Value: a string value
 * Local Variables:
 *          pos, an int value that holds the position index of ':' character
 *          value, a string value that holds the value after ':' character
 * Assistance Received: None
 **********************************************************************/
std::string Utils::getValue(std::string &line) {
    auto pos = line.find(':');
    std::string value = line.substr(pos+1);
    return value;
}

/**********************************************************************
 * Function Name: toCards
 * Purpose: To convert a string to Cards object
 * Parameters:
 *          a_card, a string value that holds the string representation of
 *          card.
 * Return Value: Cards object
 * Local Variables:
 *          t_face, a string value that holds the face of card.
 *          t_suite, a string value that holds the suite of card.
 *          temp, a Cards object that represents the string of card.
 * Assistance Received: None
 **********************************************************************/
Cards Utils::toCards(string a_card) {
    string t_face = a_card.substr(0, a_card.length()-1);
    string t_suite = a_card.substr(a_card.length()-1);
    Cards temp(t_face, t_suite);
    return temp;
}
