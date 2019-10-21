//
// Created by bibhash on 9/11/19.
//

#include "Human.hpp"

void Human::play() {
    int choice;
    do {
        cout << "Current Player: Human" << endl;
        cout    << "1. Save the game.\n" \
                << "2. Make a move.\n" \
                << "3. Ask for help.\n" \
                << "4. Quit the game." << endl;
        cin >> choice;

        if (choice == 3) {
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

        int input;

        do {
            cout << ">Do you want to: \n";
            cout << "1. Assemble possible hands.\n";
            cout << "2. Go Out.\n";
            cout << "3. Continue playing.\n";
            cin >> input;

            if (input == 1) {
                vector<vector<Cards>> arrangedHand = assemblePossibleHand();
                printAssembledHand(arrangedHand);
            }

        } while(input == 1 || input < 0 || input > 3);

        if (input == 2) {
            printCanGoOut();
        }
    }
}

void Human::pickCard() {
    int choice;
    do {
        cout    << ">From which pile do you want to pick the card? \n" \
                << "1. Draw pile\n2. Discard pile\n( Enter -1 to get hint )"<< endl;
        cin >> choice;

        if (choice == -1) {
            string pile = whichPileToChoose();
            printChosenPile(pile);
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

    string input;
    Cards discardingCard;
    int cardIndex;

    do {
        cin.ignore();
        cout    << ">Which card do you want to discard? \n" \
                << getHandAsString() << "\n" \
                << ">Enter the card to discard OR Enter -1 to get hint. " << endl;
        cin >> input;

        discardingCard = Utils::toCards(input);

        if (input == "-1") {
            int whichCard = whichCardToDiscard();
            if (whichCard == -999) {
                cout << "++++\nYou need at least four cards in your hand to discard a card \n++++" << endl;
            }
            else {
                cout << "++++\nHINT: You should discard " << hand[whichCard].toString() << " because it will help you get a lower score. \n++++" << endl;
            }
        }

        cardIndex = getCardIndex(hand, discardingCard);

    } while (cardIndex < 0);

    deck->discard(hand[cardIndex]);
    removeFromHand(cardIndex);
}

void Human::goOut() {
    this->goneOut = true;
    cout << "^*^*^*^*^\nHuman has gone out\n^*^*^*^*^" << endl;
}

void Human::getHint() {
    int choice;
    do {
        cout << "Hints:\n";
        cout << "1. Whether to draw from draw pile or discard pile.\n";
        cout << "2. How to assemble books and runs with the current hand.\n";
        cout << "3. Whether to go out or not." << endl;
        cout << ">Please enter the Hint # you would like: ";
        cin >> choice;
    } while (choice < 0 || choice > 3);

    switch (choice) {
        case 1: {
            string pile = whichPileToChoose();
            printChosenPile(pile);
            break;
        }

        case 2: {
            vector<vector<Cards>> arrangedHand = assemblePossibleHand();
            printAssembledHand(arrangedHand);
            break;
        }

        case 3:
            printCanGoOut();
            break;

        default:
            break;
    }
}

void Human::printChosenPile(string const &a_pile) {
    cout << "++++\nHINT: You should pick from the " << a_pile << " pile because";
    if (a_pile == "discard") {
        cout << " discard pile card helps you to make more runs or books and decrease your hand score. \n++++" << endl;
    }
    else {
        cout << " discard pile card does not help you to make any more runs or books. Draw pile might have a better card. \n++++" << endl;
    }
}

void Human::printAssembledHand(vector<vector<Cards>> const &a_arranged) {
    cout << "++++\nYou can arrange your hand as\n++++\n";
    for (auto const& eachHand : a_arranged) {
        for (auto eachCard : eachHand) {
            cout << eachCard.toString() << " ";
        }
        cout << " | ";
    }
    cout << " Hand Score: " << getHandScore();
    cout << "\n" << endl;
}

void Human::printCanGoOut() {
    if (canGoOut(hand)) {
        cout << "++++\nYou may go out.\n++++\n" << endl;
        goOut();
    }
    else {
        cout << "++++\nYou cannot go out. There are still unaccounted cards in your hand! \n++++\n" << endl;
    }
}