//
// Created by bibhash on 9/11/19.
//

#ifndef FIVE_CROWNS_CPP_HUMAN_HPP
#define FIVE_CROWNS_CPP_HUMAN_HPP

#include "Player.hpp"
#include <iostream>

using namespace std;

class Human : public Player {
public:
    Human();
    string getType() { return type; }
    void setType(string type) { this->type = type; }
    void play();
    void goOut();
    void pickCard();

private:
    void getHint();
};


#endif //FIVE_CROWNS_CPP_HUMAN_HPP
