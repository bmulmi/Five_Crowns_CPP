//
// Created by bibhash on 9/11/19.
//

#ifndef FIVE_CROWNS_CPP_PLAYER_HPP
#define FIVE_CROWNS_CPP_PLAYER_HPP


#include <vector>
#include <iostream>
#include "Cards.hpp"

using namespace std;

class Player {
public:
    Player();
    ~Player();
    int getScore() { return score; }
    void updateScore(int score) { this->score += score; }
    void setScore( int score ) { this->score = score; }
    void setHand (vector<Cards> hand) { this->hand = hand; }
    string getHand() {
        string temp = "";
        for (auto a_card : this->hand) {
            temp += a_card.toString() + " ";
        }
        return temp;
    }
    virtual string getType()=0;

protected:
    int score;
    vector<Cards> hand;

private:

};


#endif //FIVE_CROWNS_CPP_PLAYER_HPP
