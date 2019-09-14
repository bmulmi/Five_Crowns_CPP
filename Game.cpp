//
// Created by bibhash on 9/11/19.
//

#include "Game.hpp"
using namespace std;

Game::Game() {

}

Game::Game(int roundNumber) {
    this->roundNumber = roundNumber;
}

Game::~Game() {

}

void Game::start() {
    int nextPlayer = toss();
    if (nextPlayer == 0) {
        player[0] = new Human();
        player[1] = new Computer();
    }
    else {
        player[0] = new Computer();
        player[1] = new Human();
    }
    cout << "Now, Lets get started!" << endl;

    Round r(1, player);
    r.play();

    //while (roundNumber < 12) {
        // create the round
        // play the round

        // see if the round is save or quit

    //}
    //declare winner()

}

int Game::toss() {
    char side;
    do {
        cout << "Time for a toss. Heads or Tails (h/t)? ";
        cin >> side;
    } while (side != 'h' && side != 't');

    srand(time(0));
    int winner = rand() % 2;
    if ((winner == 0 && side == 'h') || (winner == 1 && side == 't')) {
        cout << "Congratulations! You won the toss." << endl;
        return 0;
    }
    else {
        cout << "Sorry, you lost the toss." << endl;
        return 1;
    }
}

void Game::load(vector<string> info) {
    string nextPlayer = toLowerCase(info[info.size()-1]);
    info.pop_back();
    string human = "human";

    cout << "Next player: " << nextPlayer << endl;
    if (isEqual(human, nextPlayer)) {
        player[0] = new Human();
        player[1] = new Computer();
    }
    else {
        player[0] = new Computer();
        player[1] = new Human();
    }

    cout << "first player: " << player[0]->getType();
    cout << "second player: " << player[1]->getType();

    for (auto each : info) {
        cout << each << endl;
    }
}
