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
    string nextPlayer = Utilities::toLowerCase(info[info.size()-1]);
//    nextPlayer = Utilities::trim(nextPlayer);

//    nextPlayer.erase(remove(nextPlayer.begin(), nextPlayer.end(), ' '), nextPlayer.end());

    info.pop_back();

    cout << "Next player: " << nextPlayer << endl;

    if (nextPlayer == "human") {
        player[0] = new Human();
        player[1] = new Computer();
    }
    else if (nextPlayer == "computer"){
        player[0] = new Computer();
        player[1] = new Human();
    }
    else {
        cerr << "Invalid Next Player in the serialization file! So, player goes first." << endl;
        player[0] = new Human();
        player[1] = new Computer();
    }

    Round r(this->roundNumber, player);
    r.load(info);
}
