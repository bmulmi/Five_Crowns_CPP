//
// Created by bibhash on 9/11/19.
//

#include "Player.hpp"

Player::Player() {
    score = 0;
    goneOut = false;
    saveGame = false;
    quitGame = false;
    hand.clear();
}

string Player::getHandAsString() {
    string temp = "";

    for (auto a_card : this->hand) {
        temp += a_card.toString() + " ";
    }

    return temp;
}

string Player::getHandWithIndex() {
    string temp = "";

    int i = 0;
    for (auto a_card : this->hand) {
        temp += a_card.toString() + " --> " + to_string(i) + "  ";
        i++;
    }

    return temp;
}

// checks to see if the player can go out or not
bool Player::canGoOut(vector<Cards> a_hand) {
    // make a copy of the hand
    vector<Cards> currHand = a_hand;
    int handSize = currHand.size();

    if ((currHand.size() < 6) && (isRun(currHand) != NOT_A_RUN || isBook(currHand) != NOT_A_BOOK)) {
        return true;
    }

    else {
        vector<vector<Cards>> permutedHands;

        // get all the permutations of this hand
        permute(currHand, 0, currHand.size()-1, permutedHands);

        // get all the combination indices of this size of hand
        vector<vector<int>> combinations = getCombinationIndices(currHand.size());

        for (auto eachHand : permutedHands) {
            bool comboFound = false;
            for (auto eachCombo : combinations) {
                if (checkCombo(eachHand, eachCombo) == 0) {
                    comboFound = true;
                    break;
                }
            }
            if (comboFound) {
                return true;
            }
        }
        return false;
    }
}



string Player::whichPileToChoose() {
    deck = &Deck::getInstanceOfDeck(2);
    string chosenPile = "";
    // take the discard pile card
    Cards pickedCard = deck->showDiscardCard();

    // pick if joker
    if (pickedCard.isJoker()) {
        return "Discard";
    }

    Deck* deck = &Deck::getInstanceOfDeck(2);
    string wildCard = deck->getWildCardFace();

    // pick if wildCard
    if (pickedCard.getFace() == wildCard) {
        return "Discard";
    }

    // make a copy of hand
    vector<Cards> copyHand = hand;
    copyHand.push_back(pickedCard);
    // picked card is the last card in the hand
    // now remove every card of the hand and see if the player canGoOut with the newly picked card
    for (int i = 0; i < hand.size(); i++){
        vector<Cards> temp = copyHand;
        temp.erase(temp.begin() + i);
        if (canGoOut(temp)) {
            return "Discard";
        }
    }

    return "Draw";
}

string Player::whichCardToDiscard() {
    // the card with the highest score
}

vector<vector<Cards>> Player::assemblePossibleHand() {
    vector<Cards> currHand = hand;

    vector<vector<Cards>> permutedHands;

    // get all the permutations of this hand
    permute(currHand, 0, currHand.size()-1, permutedHands);

    // get all the combination indices of this size of hand
    vector<vector<int>> combinations = getCombinationIndices(currHand.size());

    // to store the perfect combination if found
    vector<Cards> tempHand;
    vector<int> combo;
    int leastScore = INTMAX_MAX;
    for (auto eachHand : permutedHands) {
        for (auto eachCombo : combinations) {
            // get the score from this combination
            int currScore = checkCombo(eachHand, eachCombo);

            // store the hand and combo of the least score calculated from combo
            if (currScore < leastScore) {
                tempHand = eachHand;
                combo = eachCombo;
            }
        }
    }

    vector<vector<Cards>> assembledHands;
    for (int i = 0; i < combo.size() - 1; i++) {
        int start = combo[i];
        int end = combo[i+1];

        vector<Cards> comboHand (permutedHands.begin()+start, permutedHands.begin()+end);
        assembledHands.push_back(comboHand);
    }

    return assembledHands;
    // return the temp hand and combination with the least score
}

void Player::Hint() {

}
