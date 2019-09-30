//
// Created by bibhash on 9/11/19.
//

#include "Computer.hpp"

Computer::Computer() {

}

void Computer::play() {
    int choice;
    do {
        cout << "Current Player: Computer" << endl;
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
            goOut();
        }
    }
}

void Computer::pickCard() {
    cout << getType() << endl;
    deck = &Deck::getInstanceOfDeck(2);

    // choose a pile
    string chosenPile = whichPileToChoose();

    // pick from the pile
    Cards cardPicked;
    if (chosenPile == "discard") {
        cout << "@@@@ Computer chose " << chosenPile << " pile because it helped in making a run or a book. @@@@\n";
        cardPicked = deck->drawDiscardCard();
    }
    else {
        cout << "@@@@ Computer chose " << chosenPile
        << " pile to pick the card because discard pile card does not help in making a run or a book. @@@@\n";
        cardPicked = deck->drawCard();
    }
    this->hand.push_back(cardPicked);

    // choose card to discard
    int discardIndex = whichCardToDiscard();
    cout << "@@@@ Computer discarded " << hand[discardIndex].toString() << " card because it made the score lower. @@@@\n" << endl;

    // discard the card
    deck->discard(hand[discardIndex]);
    removeFromHand(discardIndex);
}

void Computer::goOut() {
    this->goneOut = true;
    cout << "@@@@ " << this->getType() << " has gone out. @@@@" << endl;
}