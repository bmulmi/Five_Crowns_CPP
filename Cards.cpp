/*
 ************************************************************
 * Name: Bibhash Mulmi                                      *
 * Project: P1 Five Crowns CPP                              *
 * Class: OPL Fall 19                                       *
 * Date: 10/23/2019                                         *
 ************************************************************
*/

// Created by bibhash on 9/10/19.


#include "Cards.hpp"

Cards::Cards(string& face, string &suite) {
    this->face = face;
    this->suite = suite;
}

/**********************************************************************
* Function Name: isJoker
* Purpose: To check if the Card object is a Joker Card
* Parameters:
*              None
* Return Value: boolean
* Local Variables:
*              None
* Algorithm:
*              1) Return true if Card's face is J AND it's suite is either 1, 2 or 3.
*              2) Else return false.
* Assistance Received: None
**********************************************************************/
bool Cards::isJoker() const{
    return (this->face == "J" && (this->suite == "1" || this->suite == "2" || this->suite == "3"));
}

bool operator==(const Cards &left, const Cards &right) {
    return (left.face == right.face && left.suite == right.suite);
}

/**********************************************************************
* Function Name: getFaceValue
* Purpose: To calculate the Face Value of the Card Object
* Parameters:
*               None
* Return Value: The integer value of the Card object
* Local Variables:
*               temp, a string to store the face of the card
* Algorithm:
*               1) Return 50 if Card is Joker.
*               2) If temp is X, return 10.
*               3) Else if temp is J, return 11.
*               4) Else if temp is Q, return 12.
*               5) Else if temp is K, return 13.
*               6) Else return the integer value of temp.
* Assistance Received: None
**********************************************************************/
int Cards::getFaceValue() const {
    string temp = this->face;

    if (this->isJoker()) return 50;

    if (temp=="X") return 10;
    else if (temp == "J") return 11;
    else if (temp == "Q") return 12;
    else if (temp == "K") return 13;
    else return stoi(temp);
}