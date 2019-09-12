//
// Created by bibhash on 9/11/19.
//

#ifndef FIVE_CROWNS_CPP_COMPUTER_HPP
#define FIVE_CROWNS_CPP_COMPUTER_HPP

#include <iostream>
#include "Player.hpp"
using namespace std;

class Computer : public Player {
public:
    Computer();
    string getType() { return "Computer "; }

};


#endif //FIVE_CROWNS_CPP_COMPUTER_HPP
