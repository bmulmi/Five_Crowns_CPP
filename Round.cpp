//
// Created by bibhash on 9/12/19.
//

#include <iomanip>
#include "Round.hpp"

Round::Round() {

}

Round::Round(int roundNumber, Player* player[]) {
    this->roundNumber = roundNumber;
    this->player = player;
    this->deck = &Deck::getInstanceOfDeck(2);
    this->totalNumPlayers = 2;
}

Round::~Round() {
    delete deck;
}

// this starts a new fresh round
void Round::play() {
    // shuffle cards
    deck->shuffleDeck();

    // set players hands
    distributeCards();

    // set the discard pile
    deck->discard(deck->drawCard());

    // set scores to zero
    for (int i = 0; i < totalNumPlayers; i++) {
        player[i]->setScore(0);
    }

    start();
}

void Round::start() {
    // this is only for two player game
    // TODO: change this algorithm for more than three players
    nextPlayer = player[1]->hasGoneOut() ? 1 : 0;

    while (!roundEnded()) {
        printRoundStatus();

        player[nextPlayer]->play();

        if (player[nextPlayer]->hasQuitGame()) {
            cout << "Quitting the game..." << endl;
            exit (1);
        }

        if (player[nextPlayer]->hasSaveGame()) {
            saveGame();
            // change the save game flag of the player
            player[nextPlayer]->setSaveGame(false);
        }
        else {
            nextPlayer = (nextPlayer + 1) % totalNumPlayers;
        }
    }
}

void Round::load() {
    // sets the hands
    // sets the discard pile
    // sets the draw pile

}

// sets hands of the players
void Round::distributeCards() {
    for (int i = 0; i < totalNumPlayers; i++) {
        vector<Cards> hand;
        for (int j = 0; j < roundNumber + 2; j++) {
            hand.push_back(deck->drawCard());
        }
        player[i]->setHand(hand);
    }
}

void Round::printRoundStatus() {
    cout << "--------------------------------------------------------------------------------------------------" << endl;
    cout << left << setw(10) << "Round Number: " << roundNumber << endl;
    cout << "\n";
    for (int i = 0; i < totalNumPlayers; i++) {
        cout << setw(10) << player[i]->getType() << "\n";
        cout << setw(10) << "Hand " << player[i]->getHand() << endl;
        cout << setw(10) << "Score " << player[i]->getScore() << endl;
        cout << "\n";
    }
    cout << setw(10) << "Discard Pile: " << deck->getDiscardCard().toString() << endl;
    cout << setw(10) << "\nDraw Pile: ";
    deck->showDrawPile();
    cout << endl;
    cout << "--------------------------------------------------------------------------------------------------" << endl;

}

bool Round::roundEnded() {
    for (int i = 0; i < totalNumPlayers; i++) {
        if (player[i]->hasGoneOut()) return true;
    }
    return false;
}

void Round::saveGame() {
    cout << "Saving Game..." << endl;


}