/*
 ************************************************************
 * Name: Bibhash Mulmi                                      *
 * Project: P1 Five Crowns CPP                              *
 * Class: OPL Fall 19                                       *
 * Date: 10/23/2019                                         *
 ************************************************************
*/

// Created by bibhash on 9/11/19.


#include "Human.hpp"

/**********************************************************************
 * Function Name: play
 * Purpose: To play human's turn
 * Parameters:
 *              None
 * Return Value: None
 * Local Variables:
 *              choice, an int value. Holds the user's menu choice.
 * Algorithm:
 *               1) Display the menu and get the user's input.
 *               2) if choice is 1, set save game flag and return
 *               3) if choice is 4, set quit game flag and return
 *               4) if choice is 2, call pick Card function and then
 *               display the go Out menu.
 *               5) if choice is 3, call getHint function.
 * Assistance Received: None
 **********************************************************************/
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

    } while (choice  > 4 || choice < 0 || choice == 3);

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
            cout << "1. See possible assembled hand.\n";
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

/**********************************************************************
 * Function Name: pickCard
 * Purpose: to let human pick a card
 * Parameters:
 *              None
 * Return Value: None
 * Local Variables:
 *              choice, an int value. It holds the value chosen by user
 *              1 for draw pile, 2 for discard pile and -1 to get hint
 *
 *              cardPicked, a Cards object. It holds the card picked by
 *              user.
 *
 *              input, a string value. It holds the card as string from
 *              user input.
 *
 *              discardingCard, a Cards object. It holds the Card object
 *              the user or computer's help chose to discard.
 * Algorithm:
 *               1) Ask the user the pile to choose and store it
 *               2) If user chooses to get help, get the pile to choose from
 *               the computer's strategy. Print the chosen pile.
 *               3) Store the card from the picked pile
 *               4) Ask user for the card to discard.
 *               5) If user chooses to get help, get the discarding card index
 *               from the computer's strategy. Print the card to discard.
 *               6) Discard the chosen card.
 * Assistance Received: None
 **********************************************************************/
void Human::pickCard() {
    // ----- pick a card -----
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

    // ----- discard a card -----
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

/**********************************************************************
 * Function Name: goOut
 * Purpose: To set goneOut flag of the human
 * Parameters:
 *              None
 * Return Value: None
 * Local Variables:
 *              None
 * Assistance Received: None
 **********************************************************************/
void Human::goOut() {
    this->goneOut = true;
    cout << "^*^*^*^*^\nHuman has gone out\n^*^*^*^*^" << endl;
}

/**********************************************************************
 * Function Name: getHint
 * Purpose: To display Hint menu and display the help
 * Parameters:
 *              None
 * Return Value: None
 * Local Variables:
 *              choice, an int value. It holds the user's input.
 * Algorithm:
 *               1) Display the Hint menu.
 *               2) Store the user's choice.
 *               3) If user chooses 1, display the computer suggested pile.
 *               4) If user chooses 2, display the possible hand.
 *               5) If user chooses 3, display whether the player can go out.
 * Assistance Received: None
 **********************************************************************/
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

/**********************************************************************
 * Function Name: printChosenPile
 * Purpose: To print the computer chosen pile with reason
 * Parameters:
 *              a_pile, a string value. It holds the pile name.
 * Return Value: None
 * Local Variables:
 *              None
 * Assistance Received: None
 **********************************************************************/
void Human::printChosenPile(string const &a_pile) {
    cout << "++++\nHINT: You should pick from the " << a_pile << " pile because";
    if (a_pile == "discard") {
        cout << " discard pile card helps you to make more runs or books and decrease your hand score. \n++++" << endl;
    }
    else {
        cout << " discard pile card does not help you to make any more runs or books. Draw pile might have a better card. \n++++" << endl;
    }
}

/**********************************************************************
 * Function Name: printAssembledHand
 * Purpose: To print the assembled hand
 * Parameters:
 *              a_arranged, a vector of vector of Cards object. It holds
 *              the arranged hand combinations.
 * Return Value: None
 * Local Variables:
 *              None
 * Algorithm:
 *               1) Convert each Card from the parameter to string and
 *               display it
 * Assistance Received: None
 **********************************************************************/
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

/**********************************************************************
 * Function Name: printCanGoOut
 * Purpose: To print whether user can go out or not
 * Parameters:
 *              None
 * Return Value: None
 * Local Variables:
 *              None
 * Assistance Received: None
 **********************************************************************/
void Human::printCanGoOut() {
    if (canGoOut(hand)) {
        cout << "++++\nYou may go out.\n++++\n" << endl;
        goOut();
    }
    else {
        cout << "++++\nYou cannot go out. There are still unaccounted cards in your hand! \n++++\n" << endl;
    }
}