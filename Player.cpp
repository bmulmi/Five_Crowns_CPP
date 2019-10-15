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

int Player::getCardIndex(vector<Cards> a_hand, Cards a_card) {
    for (int i = 0; i < a_hand.size(); i++) {
        if (a_hand[i] == a_card) {
            return i;
        }
    }
    return -1;
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
    vector<vector<Cards>> assembledHands;
    int temp = getLowestScore(a_hand, assembledHands);
    return temp == 0;
//
//    if (currHand.size() < 6) {
//        return (isRun(currHand) || isBook(currHand));
//    }
//    else {
//        return getLowestScore(a_hand, assembledHands) == 0;

//
//        vector<vector<Cards>> permutedHands;
//
//        // get all the permutations of this hand
//        permute(currHand, 0, currHand.size()-1, permutedHands);
//
//        // get all the combination indices of this size of hand
//        vector<vector<int>> combinations = getCombinationIndicesToGoOut(currHand.size());
//
//        for (auto eachHand : permutedHands) {
//            bool comboFound = false;
//            for (auto eachCombo : combinations) {
//                if (checkCombo(eachHand, eachCombo) == 0) {
//                    comboFound = true;
//                    break;
//                }
//            }
//            if (comboFound) {
//                return true;
//            }
//        }
//        return false;
//    }
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

        vector<vector<int>> combinations1 = getCombinationIndicesToGoOut(temp.size());
        vector<vector<int>> combinations2 = getCombinationIndicesTOCheck(temp.size());
        vector<vector<int>> combinations;
        combinations.reserve(combinations1.size() + combinations2.size());
        combinations.insert(combinations.end(), combinations1.begin(), combinations1.end());
        combinations.insert(combinations.end(), combinations2.begin(), combinations2.end());

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
    vector<vector<int>> combinations1 = getCombinationIndicesToGoOut(currHand.size());
    vector<vector<int>> combinations2 = getCombinationIndicesTOCheck(currHand.size());
    vector<vector<int>> combinations;
    combinations.reserve(combinations1.size() + combinations2.size());
    combinations.insert(combinations.end(), combinations1.begin(), combinations1.end());
    combinations.insert(combinations.end(), combinations2.begin(), combinations2.end());

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
        if (combo.size() <= 2) {
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
    for (auto const& eachHand : permutedHands) {
        int currScore;
        // Now, check all the combination indices to go out
        for (auto const& eachCombo : combinations) {
            // get the score from this combination
            currScore = checkCombo(eachHand, eachCombo);
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

void Player::removeCards(vector<Cards> &a_hand, vector<Cards> cards) {
    for (auto each : cards) {
        for (int i = 0; i < a_hand.size(); i++) {
            if (each == a_hand[i]) {
                a_hand.erase(a_hand.begin() + i);
                break;
            }
        }
    }
}

int Player::getLowestScore(vector<Cards> &a_hand, vector<vector<Cards>> &assembled_hands) {
    int minScore = 99999;

    vector<Cards> bestCombo;
    vector<vector <Cards>> booksAndRuns = getBooksAndRuns(a_hand);

    cout << "#Books and runs found: " << booksAndRuns.size() << endl;
//
//    for (auto each : booksAndRuns) {
//        for (auto ev : each) {
//            cout << ev.toString() << " ";
//        }
//        cout << "\n";
//    }
//
    // base case
    if (booksAndRuns.empty()) {
        return calculateRealScore(a_hand);
    }
    // generate child hands of each by removing the parent cards
    else {
        for (auto each : booksAndRuns) {
            // copy the current hand
            vector <Cards> temp_hand = a_hand;

            // remove the books or runs from the hand
            removeCards(temp_hand, each);

            // calculate the score -> recursion
            int score = getLowestScore(temp_hand, assembled_hands);

            // set the minScore of this parent
            // also set the best combo of this parent
            if (score < minScore) {
                minScore = score;
                bestCombo = each;
            }
        }
        // push the best combination of this depth into the assembled hands vector
        assembled_hands.push_back(bestCombo);
    }
    return minScore;
}

vector<vector<Cards>> Player::getBooksAndRuns(vector<Cards> a_hand) {
    vector<vector<Cards>> temp;

    // check for books
    vector<Cards> temp_hand = a_hand;
    getBooksOrRuns(a_hand, temp, 0);

    // check for runs
    vector<vector<Cards>> temp_sameSuiteHands = getSameSuiteHands(temp_hand);
    for (auto each : temp_sameSuiteHands) {
        getBooksOrRuns(each, temp, 1);
    }

    return temp;
}

void Player::getBooksOrRuns(vector<Cards> a_hand, vector<vector<Cards>> &a_collection, int check_type) {
    vector<Cards> temp_hand = a_hand;
    vector<Cards> temp_jokers = extractJokerCards(temp_hand);
    vector<Cards> temp_wilds = extractWildCards(temp_hand);

    int totalJnW = temp_jokers.size() + temp_wilds.size();
    bool jokerAndWildExist = totalJnW != 0;

    if (temp_hand.empty() && totalJnW != 0) {
        // this means the hand has only jokers and wild cards
        a_collection.push_back(a_hand);
        return;
    }

    // check without jokers and wilds
    for (int i = 0; i < temp_hand.size(); i++) {
        for (int j = 1; j < temp_hand.size() + 1 - i; j++) {
            vector<Cards> curr (temp_hand.begin()+i, temp_hand.begin()+i+j);
            if (check_type == 0) {
                if (isBook(curr)) {
                    a_collection.push_back(curr);
                }
            }
            else {
                if (isRun(curr)) {
                    a_collection.push_back(curr);
                }
            }
        }
    }

    // when there are no jokers or wildcards in the hand
    // no need to go further than this command
    if (!jokerAndWildExist) {
        return;
    }

    // ---------------------------------------------
    // STEP 2: check with Jokers in each combination
    if (!temp_jokers.empty()) {
        combineAndCheck(temp_hand, temp_jokers, a_collection, check_type);
    }
    // STEP 3: check with Wild Cards in each combination
    if (!temp_wilds.empty()) {
        combineAndCheck(temp_hand, temp_wilds, a_collection, check_type);
    }

    // STEP 4: check with Jokers AND WildCards in each combination
    // reset the variables
    temp_hand = a_hand;
    temp_jokers = extractJokerCards(temp_hand);
    temp_wilds = extractWildCards(temp_hand);
    if (!temp_jokers.empty() && !temp_wilds.empty()) {
        combineTwoAndCheck(temp_hand, temp_wilds, temp_jokers, a_collection, check_type);
    }

}

void Player::combineAndCheck(vector <Cards> a_hand, vector <Cards> a_cards, vector <vector<Cards>> &collection, int check_type) {
    for (int i = 0; i < a_hand.size(); i++) {
        for (int j = 0; j < a_hand.size() + 1 - i; j++) {
            // generate the combination
            vector<Cards> curr (a_hand.begin()+i, a_hand.begin()+i+j);

            vector<Cards> cardsToCombine = a_cards;
            // check this group of cards with jokers
            while (!cardsToCombine.empty()) {
                Cards currJoker = cardsToCombine.back();
                cardsToCombine.pop_back();
                curr.push_back(currJoker);
                if (check_type == 0) {
                    if (isBook(curr)) {
                        collection.push_back(curr);
                    }
                }
                else {
                    if (isRun(curr)) {
                        collection.push_back(curr);
                    }
                }
            }
        }
    }
}

void Player::combineTwoAndCheck(vector<Cards> a_hand, vector<Cards> a_cards1, vector<Cards> a_cards2,
                                vector<vector<Cards>> &collection, int check_type) {
    for (int i = 0; i < a_hand.size(); i++) {
        for (int j = 0; j < a_hand.size() + 1 - i; j++) {
            // generate the combination
            vector<Cards> curr (a_hand.begin()+i, a_hand.begin()+i+j);
            vector<Cards> temp_cards1 = a_cards1;

            // check this group of cards with wilds
            while (!temp_cards1.empty()) {
                Cards currWilds = temp_cards1.back();
                temp_cards1.pop_back();
                curr.push_back(currWilds);

                // make a copy of the cards
                vector<Cards> copy_curr = curr;

                vector<Cards> temp_cards2 = a_cards2;
                // push each joker to the copied hand and check
                while (!temp_cards2.empty()) {
                    Cards currJoker = temp_cards2.back();
                    temp_cards2.pop_back();
                    copy_curr.push_back(currJoker);
                    if (check_type == 0) {
                        if (isBook(copy_curr)) {
                            collection.push_back(copy_curr);
                        }
                    }
                    else {
                        if (isRun(copy_curr)) {
                            collection.push_back(copy_curr);
                        }
                    }
                }
            }
        }
    }
}

vector<vector<Cards>> Player::getSameSuiteHands(vector<Cards> a_hand) {
    string const suite [5] = {"S", "C", "D", "H", "T"};
    vector<Cards> jokers = extractJokerCards(a_hand);
    vector<Cards> wilds = extractWildCards(a_hand);
    vector<vector<Cards>> temp;

    for (auto e_suite : suite) {
        vector<Cards> curr;
        for (auto e_card : a_hand) {
            if (e_card.getSuite() == e_suite) {
                curr.push_back(e_card);
            }
        }
        if (curr.size() > 1){
            // add jokers and wildcards to that group
            for (auto each : jokers) {
                curr.push_back(each);
            }
            for (auto each : wilds) {
                curr.push_back(each);
            }
            // finally add it to the returning vector
            temp.push_back(curr);
        }
    }

    return temp;
}

void Player::Hint() {

}
