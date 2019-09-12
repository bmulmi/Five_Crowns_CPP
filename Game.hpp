//
// Created by bibhash on 9/11/19.
//

#ifndef FIVE_CROWNS_CPP_GAME_HPP
#define FIVE_CROWNS_CPP_GAME_HPP


#include "Player.hpp"

class Game {
public:
    Game();
    Game(int roundNumber, Player* player[]);
    ~Game();
    void load();
    void start();

private:
    int roundNumber;
    Player** player;

};


#endif //FIVE_CROWNS_CPP_GAME_HPP
