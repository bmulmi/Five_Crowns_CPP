//
// Created by bibhash on 9/11/19.
//

#ifndef FIVE_CROWNS_CPP_GAME_HPP
#define FIVE_CROWNS_CPP_GAME_HPP


#include "Player.hpp"
#include "Human.hpp"
#include "Computer.hpp"
#include "Round.hpp"
#include "Utilities.hpp"

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <fstream>

class Game {
public:
    Game() = default;
    Game(int roundNumber);
    ~Game() = default;

    int toss();
    void load(vector<string> info);
    void start();
    void saveGame(string info);
    void declareWinner();

private:
    int roundNumber;
    Player* player[2];
};


#endif //FIVE_CROWNS_CPP_GAME_HPP
