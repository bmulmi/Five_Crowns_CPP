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
        player[0]->setType("Human");
//        player[0] = new Computer();
//        player[0]->setType("Computer 2");
        player[1] = new Computer();
        player[1]->setType("Computer");
    }
    else {
        player[0] = new Computer();
        player[0]->setType("Computer");
        player[1] = new Human();
        player[1]->setType("Human");
//        player[1] = new Computer();
//        player[1]->setType("Computer 2");
    }
    cout << "Now, Lets get started!" << endl;

    // set the scores to zero before starting a fresh game
    for (int i = 0; i < 2; i++) {
        player[i]->setScore(0);
    }


    while (roundNumber < 12) {
        Round r(roundNumber, player);
        r.play();

        if (r.isSaveAndQuit()) {
            string roundInfo = r.getSerializableInfo();
            saveGame(roundInfo);
            return;
        }

        roundNumber++;
    }
//    declare winner()

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

// sets next player and loads the round
void Game::load(vector<string> info) {
    string nextPlayer = Utils::toLowerCase(info[info.size()-1]);
    info.pop_back();

    // set the next player
    cout << "Next player: " << nextPlayer << endl;

    if (nextPlayer == "human") {
        player[0] = new Human();
        player[0]->setType("Human");
        player[1] = new Computer();
        player[1]->setType("Computer");
//        player[0] = new Computer();
//        player[0]->setType("Computer 2");
    }
    else if (nextPlayer == "computer"){
        player[0] = new Computer();
        player[0]->setType("Computer");
        player[1] = new Human();
        player[1]->setType("Human");
//        player[1] = new Computer();
//        player[1]->setType("Computer 2");
    }
    else {
        cerr << "Invalid Next Player in the serialization file! So, human goes first." << endl;
        player[0] = new Human();
        player[0]->setType("Human");
        player[1] = new Computer();
        player[1]->setType("Computer");
    }

    bool justLoaded = true;

    while (roundNumber < 12) {
        // create the round
        Round r(this->roundNumber, player);

        if (justLoaded){
            r.load(info);
            r.start();
            justLoaded = false;
        }
        else {
            r.play();
        }

        if (r.isSaveAndQuit()) {
            string roundInfo = r.getSerializableInfo();
            saveGame(roundInfo);
            return;
        }

        roundNumber++;
    }
}

// saves the string of round info into a ofstream object
void Game::saveGame(string info) {
    ofstream save;
    string filename;

    cout << "Please enter the name of the file you want to save: ";
    cin.ignore();
    cin >> filename;
    filename += ".txt";

    save.open("/home/bibhash/git_repos/Five_Crowns_CPP/savedGames/"+filename);
    save << info;
    save.close();
}