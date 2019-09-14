//
// Created by bibhash on 9/11/19.
//

#ifndef FIVE_CROWNS_CPP_FIVECROWNS_HPP
#define FIVE_CROWNS_CPP_FIVECROWNS_HPP

#include <string>
#include <iostream>
#include <fstream>

#include "Game.hpp"
#include "Player.hpp"
#include "Human.hpp"
#include "Computer.hpp"

using namespace std;

class FiveCrowns {
public:
    FiveCrowns();
    ~FiveCrowns();
    void start();
    void reset();
    void restart();

private:
    void init(int roundNumber);
    void loadGame();

    string getValue(string line) {
        auto pos = line.find(':');
        string value = line.substr(pos+1);
        return value;
    }

    Game* game;
};


#endif //FIVE_CROWNS_CPP_FIVECROWNS_HPP
