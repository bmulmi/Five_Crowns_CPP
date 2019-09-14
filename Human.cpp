//
// Created by bibhash on 9/11/19.
//

#include "Human.hpp"

Human::Human() {

}

void Human::play() {
    int choice;
    do {
        cout    << "1. Save the game.\n" \
                << "2. Make a move.\n" \
                << "3. Ask for help.\n" \
                << "4. Quit the game." << endl;
        cin >> choice;
    } while (choice  > 5 || choice < 0);

    if (choice == 1) {
        setSaveGame(true);
        return;
    }

    if (choice == 4) {
        setQuitGame(true);
        return;
    }

    if (choice == 3) {
        cout << "Asking for help..." << endl;
        play();
    }

    if (choice == 2) {
        pickCard();
    }
}

void Human::pickCard() {
    int choice;
    do {
        cout    << "From which pile do you want to pick the card? \n" \
                << "Enter 1 for draw pile, 2 for discard pile. "<< endl;
        cin >> choice;
    } while (choice != 1 && choice != 2);

    Deck* deck = &Deck::getInstanceOfDeck(2);
    Cards cardPicked;
    if (choice == 1) {
        cardPicked = deck->drawCard();
    }
    else {
        cardPicked = deck->getDiscardCard();
    }

    int handIndex;
    do {
        cout    << "Which card do you want to discard? \n" \
                << getHandWithIndex() << "\n" \
                << "Enter the index number of the card. " << endl;
        cin >> handIndex;
    } while (handIndex < 0 || handIndex > hand.size());

    deck->discard(hand[handIndex]);
    updateHand(cardPicked, handIndex);
}

void Human::goOut() {

}