//
// Created by bibhash on 9/11/19.
//

#ifndef FIVE_CROWNS_CPP_PLAYER_HPP
#define FIVE_CROWNS_CPP_PLAYER_HPP


#include <vector>
#include <iostream>
#include <algorithm>
#include "Cards.hpp"
#include "Deck.hpp"

using namespace std;

class Player {
public:
    Player();
    ~Player();
    int getScore() { return score; }
    void updateScore(int score) { this->score += score; }
    void setScore( int score ) { this->score = score; }
    void setHand (vector<Cards> hand) { this->hand = hand; }
    void removeFromHand(int discardIndex) { hand.erase(hand.begin() + discardIndex); }

    vector<Cards> getHand() { return this->hand; }
    string getHandAsString();
    string getHandWithIndex();

    virtual string getType() = 0;
    virtual void goOut() = 0;
    virtual void play() = 0;
    virtual void pickCard() = 0;

    bool hasQuitGame() { return quitGame; }
    bool hasSaveGame() { return saveGame; }
    bool hasGoneOut() { return goneOut; }
    bool canGoOut();
    bool isRun(vector<Cards> a_hand);
    bool isBook (vector<Cards> a_hand);
    bool hasSameSuite(vector<Cards> a_hand);
    bool compareIntervalCards(Cards left, Cards right);
    void sortCards(vector<Cards> &a_hand);
    void swapCards(Cards *left, Cards *right);

    vector<Cards> extractJokerAndWildCards(vector<Cards> &hand);

    void setQuitGame(bool val) { quitGame = val; }
    void setSaveGame(bool val) { saveGame = val; }
    void setGoneOut(bool val) { goneOut  = val;}


protected:
    int score;
    bool goneOut;
    bool saveGame;
    bool quitGame;
    vector<Cards> hand;

private:

};


#endif //FIVE_CROWNS_CPP_PLAYER_HPP
