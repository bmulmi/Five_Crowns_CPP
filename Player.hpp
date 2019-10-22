/*
 ************************************************************
 * Name: Bibhash Mulmi                                      *
 * Project: P1 Five Crowns CPP                              *
 * Class: OPL Fall 19                                       *
 * Date: 10/23/2019                                         *
 ************************************************************
*/

// Created by bibhash on 9/11/19.


#ifndef FIVE_CROWNS_CPP_PLAYER_HPP
#define FIVE_CROWNS_CPP_PLAYER_HPP


#include <vector>
#include <iostream>
#include <algorithm>
#include <string.h>

#include "Cards.hpp"
#include "Deck.hpp"
#include "Validate.hpp"
#include "Utilities.hpp"
#include "Assembled.hpp"

using namespace std;
using namespace Validate;

class Player {
public:
    Player();
    ~Player() = default;

    const int getScore() { return score; }
    const int getHandScore();
    const int getCardIndex(vector<Cards> a_hand, Cards a_card);
    const string getAssembledHandAsString();
    const string getHandAsString();

    void setScore( int a_score ) { this->score = a_score; }
    void setHand (vector<Cards> a_hand) { this->hand = a_hand; }
    void setQuitGame(bool val) { quitGame = val; }
    void setSaveGame(bool val) { saveGame = val; }
    void setGoneOut(bool val) { goneOut  = val;}
    void updateScore(int a_score) { this->score += a_score; }
    void removeFromHand(int discardIndex) { hand.erase(hand.begin() + discardIndex); }

    bool hasQuitGame() { return quitGame; }
    bool hasSaveGame() { return saveGame; }
    bool hasGoneOut() { return goneOut; }
    bool canGoOut(vector<Cards> a_hand);

    virtual const string getType() = 0;
    virtual void setType(string type) = 0;
    virtual void goOut() = 0;
    virtual void play() = 0;
    virtual void pickCard() = 0;

protected:
    int score;
    string type;
    bool goneOut;
    bool saveGame;
    bool quitGame;
    Deck* deck;
    vector<Cards> hand;

    string whichPileToChoose();
    int whichCardToDiscard();
    vector<vector<Cards>> assemblePossibleHand();

private:
    vector<vector<Cards>> getBooksAndRuns(vector<Cards> a_hand);
    vector<vector<Cards>> getSameSuiteHands(vector<Cards> a_hand);
    int getLowestScore (vector <Cards> &a_hand, Assembled *assembled_hands);
    void getBooksOrRuns(vector<Cards> a_hand, vector<vector<Cards>> &a_collection, int check_type);
    void combineAndCheck (vector<Cards> a_hand, vector<Cards> a_cards, vector<vector<Cards>> &collection, int check_type);
    void combineTwoAndCheck (vector<Cards> a_hand, vector<Cards> a_cards1, vector<Cards> a_cards2, vector<vector<Cards>> &collection, int check_type);
    void removeCards (vector<Cards> &a_hand, vector<Cards> cards);
};


#endif //FIVE_CROWNS_CPP_PLAYER_HPP
