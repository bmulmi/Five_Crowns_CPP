//
// Created by bibhash on 9/11/19.
//

#include "Computer.hpp"

void Computer::play() {
    int choice;
    do {
        cout << "Current Player: Computer" << endl;
        cout    << "1. Save the game.\n" \
                << "2. Make a move.\n" \
                << "3. Quit the game." << endl;
        cin >> choice;
//        choice = 2;
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
    cout << getType() << " is playing."<< endl;
    deck = &Deck::getInstanceOfDeck(2);

    // choose a pile
    string chosenPile = whichPileToChoose();

    // pick from the pile
    Cards cardPicked;
    cout << "\n=-=-=-=\n" << getType() << " chose ";
    if (chosenPile == "discard") {
        cout << chosenPile << " pile because it helped in making a run or a book.\n=-=-=-=\n";
        cardPicked = deck->drawDiscardCard();
    }
    else {
        cout << chosenPile << " pile to pick the card because discard pile card did not help in making more numbers of complete runs or complete books.\n=-=-=-=\n";
        cardPicked = deck->drawCard();
    }
    this->hand.push_back(cardPicked);

    // choose card to discard
    int discardIndex = whichCardToDiscard();
    cout << "\n=-=-=-=\n" << getType() << " discarded " << hand[discardIndex].toString() << " card because it made the score lower.\n=-=-=-=\n" << endl;

    // discard the card
    deck->discard(hand[discardIndex]);
    removeFromHand(discardIndex);
}

void Computer::goOut() {
    this->goneOut = true;
    cout << "^*^*^*^*^\n" << this->getType() << " has gone out.\n^*^*^*^*^" << endl;
}