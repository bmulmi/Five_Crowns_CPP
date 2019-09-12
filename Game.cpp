//
// Created by bibhash on 9/11/19.
//

#include "Game.hpp"
#include <iostream>
using namespace std;

Game::Game() {

}

Game::Game(int roundNumber, Player* player[]) {
    this->player = player;
//    cout << "First: " << endl;
//    player[0]->printType();
//    cout << "second: " << endl;
//    player[1]->printType();
    this->roundNumber = roundNumber;
}

Game::~Game() {

}

void Game::start() {
    while (roundNumber < 12) {
        // create the round
        // play the round

        // see if the round is save or quit

    }
    //declare winner()
}

void Game::load() {

}
