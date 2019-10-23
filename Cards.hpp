/*
 ************************************************************
 * Name: Bibhash Mulmi                                      *
 * Project: P1 Five Crowns CPP                              *
 * Class: OPL Fall 19                                       *
 * Date: 10/23/2019                                         *
 ************************************************************
*/

// Created by bibhash on 9/10/19.


#ifndef FIVE_CROWNS_CPP_CARDS_HPP
#define FIVE_CROWNS_CPP_CARDS_HPP

#include <string>
using namespace std;

class Cards {
public:
    Cards() = default;
    Cards(string& face, string& suit);
    ~Cards() = default;
    friend bool operator==(const Cards &left, const Cards &right);

    //-----selectors-----
    int getFaceValue() const;
    string getSuite() const { return suite; }
    string getFace() const { return face; }

    //-----utility functions-----
    string toString() const { return face + suite; }

    bool isJoker() const;

private:
    string face;
    string suite;
};


#endif //FIVE_CROWNS_CPP_CARDS_H
