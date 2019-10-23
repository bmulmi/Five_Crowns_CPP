/*
 ************************************************************
 * Name: Bibhash Mulmi                                      *
 * Project: P1 Five Crowns CPP                              *
 * Class: OPL Fall 19                                       *
 * Date: 10/23/2019                                         *
 ************************************************************
*/

// Created by bibhash on 9/11/19.


#include "Computer.hpp"


/**********************************************************************
* Function Name: play
* Purpose: To display options for the computer to pick and play the game
*           according to the choice made
* Parameters:
*              None
* Return Value: None
* Local Variables:
*               choice, integer value that stores the user input of choice
*               number
* Algorithm:
*               1) Display the menu
*               2) Get user input
*               3) When choice is 1, set saveGame to true and return
*               4) When choice is 2, set quitGame to true and return
*               5) When choice is 3, call pickCard function, goOut if
*                  player can go out.
* Assistance Received: None
**********************************************************************/
void Computer::play() {
    int choice;
    do {
        cout << "Current Player: Computer" << endl;
        cout    << "1. Save the game.\n" \
                << "2. Make a move.\n" \
                << "3. Quit the game." << endl;
        cin >> choice;
    } while (choice  > 3 || choice < 0);


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

/**********************************************************************
 * Function Name: pickCard
 * Purpose: To pick from either discard or draw pile and discard one card
 *          using the player strategy
 * Parameters:
 *              None
 * Return Value: None
 * Local Variables:
 *              chosenPile, string to store the pile name suggested by the
 *              computer's strategy
 *
 *              cardPicked, Card object to store the picked card
 *              discardIndex, integer to store the index of the card to
 *
 *              discard suggested by computer's strategy
 *
 * Algorithm:
 *               1) Get and store the pile to choose from by calling whichPileToChoose
 *               2) Store the card picked from the pile
 *               3) Get the index of the card to discard by calling whichCardToDiscard
 *               4) Discard the card in that index of the hand
 * Assistance Received: None
 **********************************************************************/
void Computer::pickCard() {
//    cout << getType() << " is playing."<< endl;
    deck = &Deck::getInstanceOfDeck(2);

    // varialble that stores the chosen a pile
    string chosenPile = whichPileToChoose();

    // variable that stores the picked card
    Cards cardPicked;
    cout << "\n=-=-=-=\n" << getType() << " chose ";
    if (chosenPile == "discard") {
        cout << chosenPile << " pile because it helped in making a run or a book.\n=-=-=-=\n";
        cardPicked = deck->drawDiscardCard();
    }
    else {
        cout << chosenPile << " pile to pick the card because discard pile card "
                              "did not help in making more numbers of complete "
                              "runs or complete books.\n=-=-=-=\n";
        cardPicked = deck->drawCard();
    }
    this->hand.push_back(cardPicked);

    // variable that stores the card to discard
    int discardIndex = whichCardToDiscard();
    cout << "\n=-=-=-=\n" << getType() << " discarded " << hand[discardIndex].toString()
        << " card because it made the score lower.\n=-=-=-=\n" << endl;

    deck->discard(hand[discardIndex]);
    removeFromHand(discardIndex);
}

/**********************************************************************
* Function Name: goOut
* Purpose: To set the goneOut boolean to true
* Parameters:
*              None
* Return Value: None
* Local Variables: None
* Algorithm:
*               1) set goneOut to true and print the status.
* Assistance Received: None
**********************************************************************/
void Computer::goOut() {
    this->goneOut = true;
    cout << "^*^*^*^*^\n" << this->getType() << " has gone out.\n^*^*^*^*^" << endl;
}