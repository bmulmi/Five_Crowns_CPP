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
    bool isSaveAndQuit() {return saveAndQuit; }
    string getSerializableInfo();

private:
    vector<Cards> loadHands(string cards);
    deque<Cards> loadDeck(string cards);

    void distributeCards();
    void printRoundStatus();
    bool roundEnded();
    void setSaveGame(bool val) { saveAndQuit = val;}

    Player** player;
    Deck* deck;
    bool saveAndQuit;
    int nextPlayer;
    int currPlayer;
    int roundNumber;
    int totalNumPlayers;
};


#endif //FIVE_CROWNS_CPP_ROUND_HPP
