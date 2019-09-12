//
// Created by bibhash on 9/12/19.
//

#include "Round.hpp"

Round::Round() {

}

Round::Round(int roundNumber, Player* player[]) {
    this->roundNumber = roundNumber;
    this->player = player;
    this->deck = new Deck(2);
    this->totalNumPlayers = 2;
}

Round::~Round() {
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

    printRoundStatus();
    start();
}

void Round::start() {
    // loop until round has not ended
        // change players
        // get their move
    return;
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
    cout << "\nRound Number: " << roundNumber << endl;
    for (int i = 0; i < totalNumPlayers; i++) {
        cout << player[i]->getType();
        cout << "Hand: " << player[i]->getHand() << endl;
        cout << "Score: " << player[i]->getScore() << endl;
    }
    cout << "\nDiscard Pile: " << deck->getDiscardCard().toString() << endl;
    cout << "\nDraw Pile: ";
    deck->showDrawPile();
    cout << endl;
}