//
// Created by bibhash on 9/11/19.
//

#ifndef FIVE_CROWNS_CPP_COMPUTER_HPP
#define FIVE_CROWNS_CPP_COMPUTER_HPP

#include <iostream>
#include "Player.hpp"
#include "Deck.hpp"

using namespace std;

class Computer : public Player {
public:
    Computer();
    string getType() { return "Computer "; }
    void play();
    void goOut();
    void pickCard();

};


#endif //FIVE_CROWNS_CPP_COMPUTER_HPP
