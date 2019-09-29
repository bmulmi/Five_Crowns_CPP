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
bool Player::canGoOut() {
    vector<Cards> currHand = this->hand;
    int handSize = currHand.size();

    if ((currHand.size() < 6) && (isRun(currHand) ||  isBook(currHand))) {
        return true;
    }
    else {
        vector<vector<Cards>> permutedHands;
        // get all the permutations of this hand
        permute(currHand, 0, currHand.size()-1, permutedHands);

        // get all the combination indices of this size of hand
        vector<vector<int>> combinations = getCombinationIndices(currHand.size());

        cout << permutedHands.size() << " : size of permuted hands" << endl;

        // to store the perfect combination if found
        vector<Cards> tempHand;
        vector<int> combo;

        for (auto eachHand : permutedHands) {
            bool comboFound = false;
            for (auto eachCombo : combinations) {
                if (checkCombo(eachHand, eachCombo)) {
                    tempHand = eachHand;
                    combo = eachCombo;
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
