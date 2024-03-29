/*
 ************************************************************
 * Name: Bibhash Mulmi                                      *
 * Project: P1 Five Crowns CPP                              *
 * Class: OPL Fall 19                                       *
 * Date: 10/23/2019                                         *
 ************************************************************
*/

// Created by bibhash on 9/12/19.


#ifndef FIVE_CROWNS_CPP_ROUND_HPP
#define FIVE_CROWNS_CPP_ROUND_HPP


#include "Player.hpp"
#include "Deck.hpp"
#include "Utilities.hpp"

class Round {
public:
    Round() = default;
    Round(int roundNumber, Player* player[]);
    ~Round() = default;

    const string getSerializableInfo();

    /**********************************************************************
     * Function Name: isSaveAndQuit
     * Purpose: To return the saveAndQuit flag
     * Parameters: None
     * Return Value: Boolean value. True if player saved and quit, false otherwise.
     * Local Variables: None
     * Assistance Received: None
     **********************************************************************/
    bool isSaveAndQuit() {return saveAndQuit; }

    void play();
    void load(vector<string> info);
    void start();

private:
    Player** player;
    Deck* deck;
    bool saveAndQuit;
    int nextPlayer;
    int currPlayer;
    int roundNumber;
    int totalNumPlayers;

    /**********************************************************************
     * Function Name: setSaveGame
     * Purpose: To set the saveAndQuit flag
     * Parameters: val, a boolean value.
     * Return Value: None
     * Local Variables: None
     * Assistance Received: None
     **********************************************************************/
    void setSaveGame(bool val) { saveAndQuit = val;}

    vector<Cards> loadHands(string cards);
    deque<Cards> loadDeck(string cards);
    bool roundEnded();
    void distributeCards();
    void printRoundStatus();
    void endRound();
};


#endif //FIVE_CROWNS_CPP_ROUND_HPP
