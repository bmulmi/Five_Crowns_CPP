//
// Created by bibhash on 9/11/19.
//

#include "Human.hpp"

Human::Human() {

}

void Human::play() {
    int choice;
    do {
        cout << "Player: Human" << endl;
        cout    << "1. Save the game.\n" \
                << "2. Make a move.\n" \
                << "3. Ask for help.\n" \
                << "4. Quit the game." << endl;
        cin >> choice;

        if (choice == 3) {
            cout << "Asking for help..." << endl;
            getHint();
        }

    } while (choice  > 5 || choice < 0 || choice == 3);

    if (choice == 1) {
        setSaveGame(true);
        return;
    }

    if (choice == 4) {
        setQuitGame(true);
        return;
    }

    if (choice == 2) {
        pickCard();

        char input;
        do {
            cout << "Do you want to go out? (y/n) ";
            cin >> input;
        } while(input != 'y' && input != 'n');

        if (input == 'y') {
            if (canGoOut(hand)) {
                cout << "You may go out.\n" << endl;
                goOut();
            }
            else {
                cout << "You cannot go out. There are still unaccounted cards in your hand!\n" << endl;
            }
        }
    }
}

void Human::pickCard() {
    int choice;
    do {
        cout    << "From which pile do you want to pick the card? \n" \
                << "Enter 1 for draw pile, 2 for discard pile, 3 to get Help. "<< endl;
        cin >> choice;

        if (choice == 3) {
            string pile = whichPileToChoose();
            cout << "**HINT: You should pick from the " << pile << " pile**" << endl;
        }

    } while (choice != 1 && choice != 2);

    deck = &Deck::getInstanceOfDeck(2);
    Cards cardPicked;
    if (choice == 1) {
        cardPicked = deck->drawCard();
    }
    else {
        cardPicked = deck->drawDiscardCard();
    }

    this->hand.push_back(cardPicked);

    int cardIndex;

    do {
        cout    << "Which card do you want to discard? \n" \
                << getHandWithIndex() << "\n" \
                << "Enter the index number of the card or Enter -1 to get hint. " << endl;
        cin >> cardIndex;

        if (cardIndex == -1) {
            int whichCard = whichCardToDiscard();
            if (whichCard == -999) {
                cout << "**You need at least four cards in your hand to discard a card**" << endl;
            }
            else {
                cout << "**HINT: You should discard " << hand[whichCard].toString() << " because it will help you get a lower score.**" << endl;
            }
        }
    } while (cardIndex < 0 || cardIndex > hand.size());

    deck->discard(hand[cardIndex]);
    removeFromHand(cardIndex);
}

void Human::goOut() {
    this->goneOut = true;
    cout << "Human has gone out." << endl;
}

void Human::getHint() {
    int choice;
    cout << "1. Whether to draw from draw pile or discard pile.\n";
    cout << "2. How to assemble books and runs with the current hand.\n";
    cout << "3. Whether to go out or not.\n" << endl;
    cout << "Please enter the Hint # you would like: ";
    do {
        cin >> choice;
    } while (choice < 0 || choice > 3);

    switch (choice) {
        case 1: {
            string pile = whichPileToChoose();
            cout << "You should pick from the " << pile << " pile." << endl;
            break;
        }

        case 5: {
            int whichCard = whichCardToDiscard();
            if (whichCard == -999) {
                cout << "You need at least four cards in your hand to discard a card" << endl;
                break;
            }
            else {
                cout << "You should discard " << hand[whichCard].toString() << " because it will help you get a lower score" << endl;
                break;
            }
        }

        case 2: {
            vector<vector<Cards>> arrangedHand = assemblePossibleHand();
            cout << "You can arrange your hand as: \n";
            for (auto const& eachHand : arrangedHand) {
                for (auto eachCard : eachHand) {
                    cout << eachCard.toString() << " ";
                }
                cout << " | ";
            }
            cout << "\n" << endl;
            break;
        }

        case 3:
            if (canGoOut(hand)) {
                cout << "You may go out." << endl;
            }
            else {
                cout << "You cannot go out." << endl;
            }
            break;

        default:
            break;
    }
}
