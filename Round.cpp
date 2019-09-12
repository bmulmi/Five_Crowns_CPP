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
    delete player;
}

// this starts a new fresh round
void Round::play() {
    // shuffle cards
    deck->shuffleDeck();

    // set players hands
    for (int i = 0; i < totalNumPlayers; i++) {
        player[i]->setHand(deck->getCards(roundNumber + 2));
    }

    // set the draw pile

    // set the discard pile

    // set scores to zero
    // start()
}

void Round::start() {
    // loop until round has not ended
        // change players
        // get their moves
}

void Round::load() {

}