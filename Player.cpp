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

// returns the score from the current hand where joker is 50 points and wilds are 20 points
int Player::getHandScore() {
    vector<Cards> currHand = hand;
    vector<vector<Cards>> possibleCombos = assemblePossibleHand();
    int currScore = 0;
    for (auto const& each : possibleCombos) {
        if (isRun(each) || isBook(each))
            continue;
        else
            currScore += calculateRealScore(each);
    }
    return currScore;
}

// checks to see if the player can go out or not
bool Player::canGoOut(vector<Cards> a_hand) {
    // make a copy of the hand
    vector<Cards> currHand = a_hand;
    int handSize = currHand.size();

    if (currHand.size() < 6) {
        return (isRun(currHand) || isBook(currHand));
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
    string chosenPile;
    // take the discard pile card
    Cards pickedCard = deck->showDiscardCard();

    // pick if joker
    if (pickedCard.isJoker()) {
        return "discard";
    }

    Deck* deck = &Deck::getInstanceOfDeck(2);
    string wildCard = deck->getWildCardFace();

    // pick if wildCard
    if (pickedCard.getFace() == wildCard) {
        return "discard";
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
            return "discard";
        }
    }

    return "draw";
}

int Player::whichCardToDiscard() {
    vector<Cards> currHand = hand;
    int cardIndex = 0;
    int currScore = 9999;

    // if the hand size is 3
    if (currHand.size() == 3)
        return -999;

    for (int i = 0; i < currHand.size(); i++){
        vector<Cards> temp = currHand;
        // remove a card from the hand
        temp.erase(temp.begin() + i);

        // now count the score
        vector<vector<Cards>> permutedHands;
        permute(temp, 0, temp.size()-1, permutedHands);
        vector<vector<int>> combinations = getCombinationIndices(currHand.size());

        // to store the perfect combination if found
        vector<Cards> tempHand;
        vector<int> combo;

        int tempScr = getLowestScoreHand(tempHand, combo, permutedHands, combinations);
        if (tempScr < currScore) {
            currScore = tempScr;
            cardIndex = i;
        }
    }
    return cardIndex;
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

    getLowestScoreHand (tempHand, combo, permutedHands, combinations);

    vector<vector<Cards>> assembledHands;
    for (int i = 0; i < combo.size() - 1; i++) {
        int start = combo[i];
        int end = combo[i+1];

        vector<Cards> comboHand (tempHand.begin()+start, tempHand.begin()+end);
        assembledHands.push_back(comboHand);

        // for less than 6 cards in a hand, push the rest of the card
        if (combo.size() < 2) {
            vector<Cards> cHand (tempHand.begin()+end, tempHand.end());
            assembledHands.push_back(cHand);
        }
    }

    return assembledHands;
}

// returns the score after checking every possible combination in the permuted hands
// also changes tempHand and combo passed in a arguments
int Player::getLowestScoreHand(vector<Cards> &tempHand, vector<int> &combo, vector<vector<Cards>> permutedHands,
                                vector<vector<int>> combinations) {
    int leastScore = 99999;
    for (auto eachHand : permutedHands) {
        for (auto eachCombo : combinations) {
            // get the score from this combination
            int currScore = checkCombo(eachHand, eachCombo);

            // store the hand and combo of the least score calculated from combo
            if (currScore < leastScore) {
                leastScore = currScore;
                tempHand = eachHand;
                combo = eachCombo;
            }
        }
    }
    return leastScore;
}

void Player::Hint() {

}
