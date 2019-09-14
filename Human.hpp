//
// Created by bibhash on 9/11/19.
//

#ifndef FIVE_CROWNS_CPP_HUMAN_HPP
#define FIVE_CROWNS_CPP_HUMAN_HPP

#include "Player.hpp"
#include "Deck.hpp"
#include <iostream>

using namespace std;

class Human : public Player {
public:
    Human();
    string getType() { return "Human "; }
    void play();
    void goOut();
    void pickCard();

private:

};


#endif //FIVE_CROWNS_CPP_HUMAN_HPP
