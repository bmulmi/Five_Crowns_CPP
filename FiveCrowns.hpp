/*
 ************************************************************
 * Name: Bibhash Mulmi                                      *
 * Project: P1 Five Crowns CPP                              *
 * Class: OPL Fall 19                                       *
 * Date: 10/23/2019                                         *
 ************************************************************
*/

// Created by bibhash on 9/11/19.


#ifndef FIVE_CROWNS_CPP_FIVECROWNS_HPP
#define FIVE_CROWNS_CPP_FIVECROWNS_HPP

#include <string>
#include <iostream>
#include <fstream>

#include "Game.hpp"
#include "Player.hpp"
#include "Human.hpp"
#include "Computer.hpp"
#include "Utilities.hpp"

using namespace std;

class FiveCrowns {
public:
    FiveCrowns() = default;
    ~FiveCrowns();
    void start();
    void reset();
    void restart();

private:
    void init(int roundNumber);
    void loadGame();
    Game* game;
};


#endif //FIVE_CROWNS_CPP_FIVECROWNS_HPP
