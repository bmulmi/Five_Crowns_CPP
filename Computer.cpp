//
// Created by bibhash on 9/11/19.
//

#include "Computer.hpp"

Computer::Computer() {

}

void Computer::play() {
    int choice;
    do {
        cout << "Player: Computer" << endl;
        cout    << "1. Save the game.\n" \
                << "2. Make a move.\n" \
                << "3. Quit the game." << endl;
        cin >> choice;
    } while (choice  > 4 || choice < 0);

    if (choice == 1) {
        setSaveGame(true);
        return;
    }

    if (choice == 3) {
        setQuitGame(true);
        return;
    }

    if (choice == 2) {
        pickCard();
        if (canGoOut(hand)) {
            cout << "@@@@Computer can go out.@@@@" << endl;
            goOut();
        }
    }
}

void Computer::pickCard() {
    deck = &Deck::getInstanceOfDeck(2);

    // choose a pile
    string chosenPile = whichPileToChoose();
    cout << "@@@@Computer chose " << chosenPile << " to pick the card.@@@@\n";

    // pick from the pile
    Cards cardPicked;
    if (chosenPile == "discard") {
        cardPicked = deck->drawDiscardCard();
    }
    else {
        cardPicked = deck->drawCard();
    }
    this->hand.push_back(cardPicked);

    // choose card to discard
    int discardIndex = whichCardToDiscard();
    cout << "@@@@Computer discarded " << hand[discardIndex].toString() << " card.@@@@\n" << endl;

    // discard the card
    deck->discard(hand[discardIndex]);
    removeFromHand(discardIndex);
}

void Computer::goOut() {
    this->goneOut = true;
}