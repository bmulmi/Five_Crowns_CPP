//
// Created by bibhash on 9/11/19.
//

#include "Computer.hpp"

Computer::Computer() {

}

void Computer::play() {
    int choice;
    do {
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
        cout << "Computer played...";
//        pickCard();
//        if (canGoOut()) {
//            goOut();
//        }
    }
}

void Computer::pickCard() {
    Deck* deck = &Deck::getInstanceOfDeck(2);

    // make a copy of the hand for now
    vector<Cards> tempHand = this->hand;

    // copy the discard pile card into a temp hand
    Cards cardPicked = deck->showDiscardCard();
    tempHand.push_back(cardPicked);

    int erasedCardIndex;
    for (int i = 0; i < tempHand.size(); i++) {
        // remove a card from the hand and check if a run or book can be arranged
        vector<Cards> temp = tempHand;
        temp.erase(temp.begin() + i);

        // TODO: get permutations of this temp
        //  check combination of each permutation
        //  if a combination works then discard the erased card and pick the discard pile card
        //  else if none of the combination works then calculate score of each combination
        //  and pick the one with the score less than the current hand
        //  else pick the draw pile card
    }



}

void Computer::goOut() {

}