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
#include "Validate.hpp"

using namespace std;
using namespace Validate;

class Player {
public:
    Player();
    ~Player() = default;
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

    void setQuitGame(bool val) { quitGame = val; }
    void setSaveGame(bool val) { saveGame = val; }
    void setGoneOut(bool val) { goneOut  = val;}


protected:
    int score;
    bool goneOut;
    bool saveGame;
    bool quitGame;
    Deck* deck;
    vector<Cards> hand;


private:

};


#endif //FIVE_CROWNS_CPP_PLAYER_HPP
