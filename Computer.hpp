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
    Computer() = default;
    ~Computer() = default;

    const string getType() override { return type; }

    void setType(string type) override { this->type = type; }

    void play() override;
    void goOut() override;
    void pickCard() override;
};


#endif //FIVE_CROWNS_CPP_COMPUTER_HPP
