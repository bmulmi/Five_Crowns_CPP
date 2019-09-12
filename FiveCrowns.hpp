//
// Created by bibhash on 9/11/19.
//

#ifndef FIVE_CROWNS_CPP_FIVECROWNS_HPP
#define FIVE_CROWNS_CPP_FIVECROWNS_HPP

#include <string>
#include <iostream>
#include <cstdlib>
#include <ctime>

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
    void init(int roundNumber, int nextPlayer);
    void loadGame(string filename);

    int toss();

//    int numPlayers = 2;
    Game* game;
    Player* player[2];
};


#endif //FIVE_CROWNS_CPP_FIVECROWNS_HPP
