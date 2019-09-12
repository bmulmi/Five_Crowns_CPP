//
// Created by bibhash on 9/12/19.
//

#ifndef FIVE_CROWNS_CPP_ROUND_HPP
#define FIVE_CROWNS_CPP_ROUND_HPP


#include "Player.hpp"
#include "Deck.hpp"

class Round {
public:
    Round();
    Round(int roundNumber, Player* player[]);
    ~Round();
    void play();
    void load();
    void start();

private:
    Player** player;
    Deck* deck;
    int roundNumber;
    int totalNumPlayers;
};


#endif //FIVE_CROWNS_CPP_ROUND_HPP
