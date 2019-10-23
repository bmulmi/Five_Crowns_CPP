/*
 ************************************************************
 * Name: Bibhash Mulmi                                      *
 * Project: P1 Five Crowns CPP                              *
 * Class: OPL Fall 19                                       *
 * Date: 10/23/2019                                         *
 ************************************************************
*/

// Created by bibhash on 9/11/19.


#ifndef FIVE_CROWNS_CPP_COMPUTER_HPP
#define FIVE_CROWNS_CPP_COMPUTER_HPP

#include <iostream>
#include "Player.hpp"
#include "Deck.hpp"

using namespace std;

class Computer : public Player {
public:
    Computer() = default;
    ~Computer() = default;

    //-----selectors-----
    string getType() const override { return type; }

    //-----mutators-----
    inline void setType(string type) override { this->type = type; }

    //-----inherited virtual functions-----
    void play() override;
    void goOut() override;
    void pickCard() override;
};


#endif //FIVE_CROWNS_CPP_COMPUTER_HPP
