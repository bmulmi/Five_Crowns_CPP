/*
 ************************************************************
 * Name: Bibhash Mulmi                                      *
 * Project: P1 Five Crowns CPP                              *
 * Class: OPL Fall 19                                       *
 * Date: 10/23/2019                                         *
 ************************************************************
*/

// Created by bibhash on 9/11/19.


#ifndef FIVE_CROWNS_CPP_HUMAN_HPP
#define FIVE_CROWNS_CPP_HUMAN_HPP

#include "Player.hpp"
#include <iostream>

using namespace std;

class Human : public Player {
public:
    Human() = default;
    ~Human() = default;

    //----selectors-----
    string getType() const override { return type; }

    //-----mutators-----
    void setType(string type) override { this->type = type; }

    //-----inherited virtual functions-----
    void play() override;
    void goOut() override ;
    void pickCard() override ;

private:
    //-----utility functions-----
    void getHint();
    void printChosenPile(string const &a_pile);
    void printAssembledHand(vector<vector<Cards>> const &a_arranged);
    void printCanGoOut();
};


#endif //FIVE_CROWNS_CPP_HUMAN_HPP
