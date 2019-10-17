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
    Human() = default;
    ~Human() = default;

    const string getType() override { return type; }

    void setType(string type) override { this->type = type; }

    void play() override;
    void goOut() override ;
    void pickCard() override ;

private:
    void getHint();
};


#endif //FIVE_CROWNS_CPP_HUMAN_HPP
