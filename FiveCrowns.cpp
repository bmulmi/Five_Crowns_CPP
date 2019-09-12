//
// Created by bibhash on 9/11/19.
//

#include "FiveCrowns.hpp"

FiveCrowns::FiveCrowns() {

}

FiveCrowns::~FiveCrowns() {
    reset();
}

void FiveCrowns::start() {
    cout << "Welcome to Five Crowns!" << endl;
    char load;
    do {
        cout << "Do you want to load game? (y/n)" << endl;
        cin >> load;
    } while(load != 'y' && load != 'n');

    string filename;
    if (load == 'y') {
        cout << "What is the name of the saved file?" << endl;
        cin >> filename;
        filename.append(".txt");
        loadGame(filename);
    }
    else {
        int nextPlayer = toss();
        init(1, nextPlayer);
    }

}

int FiveCrowns::toss() {
    char side;
    do {
        cout << "Time for a toss. Heads or Tails (h/t)?" << endl;
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

void FiveCrowns::restart() {

}

void FiveCrowns::reset() {

}

// initializes the round number
// next player: 0 for human, 1 for computer
void FiveCrowns::init(int roundNumber, int nextPlayer) {
    if (nextPlayer == 0) {
        player[0] = new Human();
        player[1] = new Computer();
    }
    else {
        player[0] = new Computer();
        player[1] = new Human();
    }
    game = new Game(roundNumber, player);
    game->start();
}

void FiveCrowns::loadGame(string filename) {
    // get the round number
    // put everything into a vector of string
    // get the last line as the next player
    // call init
    // game->start();
}
