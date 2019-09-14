//
// Created by bibhash on 9/12/19.
//

#ifndef FIVE_CROWNS_CPP_ROUND_HPP
#define FIVE_CROWNS_CPP_ROUND_HPP


#include "Player.hpp"
#include "Deck.hpp"
#include "Utilities.hpp"

class Round {
public:
    Round();
    Round(int roundNumber, Player* player[]);
    ~Round();
    void play();
    void load(vector<string> info);
    void start();

private:
    vector<Cards> loadHands(string cards);
    deque<Cards> loadDeck(string cards);
    void distributeCards();
    void printRoundStatus();
    void saveGame();
    bool roundEnded();
    Player** player;
    Deck* deck;
    int nextPlayer;
    int roundNumber;
    int totalNumPlayers;
};


#endif //FIVE_CROWNS_CPP_ROUND_HPP
