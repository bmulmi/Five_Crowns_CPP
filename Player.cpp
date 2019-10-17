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
    vector<vector<Cards>> possibleCombos = assemblePossibleHand();

    // the unaccounted cards are at the back of the assembled hand.
    vector<Cards> scoreHand = possibleCombos.back();

    int currScore = calculateRealScore(scoreHand);
    return currScore;
}

// checks to see if the player can go out or not
bool Player::canGoOut(vector<Cards> a_hand) {
    Assembled *assembledHands = new Assembled(hand);
    int temp = getLowestScore(a_hand, assembledHands);
    return temp == 0;
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

    string wildCard = deck->getWildCardFace();

    // pick if wildCard
    if (pickedCard.getFace() == wildCard) {
        return "discard";
    }

    vector<Cards> copyHand = hand;

    // score of hand before picking discard card
    Assembled *assembledHand = new Assembled(copyHand);

    int scr = getLowestScore(copyHand, assembledHand);
    bool chooseDiscard = false;

    // now pick the discard card
    copyHand.push_back(pickedCard);

    // now remove every card of the previous hand AND
    // check if the player will have more books or runs with lower score with the newly picked card
    for (int i = 0; i < hand.size(); i++){
        vector<Cards> temp = copyHand;
        temp.erase(temp.begin() + i);

        Assembled *curr_assembledHand = new Assembled(temp);

        int curr_scr = getLowestScore(temp, curr_assembledHand);
        // TODO:
//        if (!curr_assembledHand->bestCombo.empty() && curr_assembledHands.size() > assembledHands.size() && curr_scr < scr) {

        if (!curr_assembledHand->bestCombo.empty() && curr_assembledHand->size() > assembledHand->size() && curr_scr < scr) {
            assembledHand = curr_assembledHand;
            scr = curr_scr;
            chooseDiscard = true;
        }
    }

    if (chooseDiscard) {
        return "discard";
    }
    else {
        return "draw";
    }
}

int Player::whichCardToDiscard() {
    vector<Cards> currHand = hand;
    int cardIndex = 0;
    int currScore = 99999;

    // if the hand size is 3
    if (currHand.size() == 3)
        return -999;

    deck = &Deck::getInstanceOfDeck(2);
    string wildCard = deck->getWildCardFace();

    for (int i = 0; i < currHand.size(); i++){
        vector<Cards> temp = currHand;

        if (currHand[i].isJoker() || currHand[i].getFace() == wildCard) {
            continue;
        }

        // remove a card from the hand
        temp.erase(temp.begin() + i);

        // now count the score;
        Assembled *assembledHand = new Assembled(temp);

        int tempScr = getLowestScore(temp, assembledHand);
        if (tempScr < currScore) {
            currScore = tempScr;
            cardIndex = i;
        }
    }
    return cardIndex;
}

vector<vector<Cards>> Player::assemblePossibleHand() {
    vector<Cards> currHand = hand;
    Assembled *assembledHand = new Assembled(currHand);

    int scr = getLowestScore (currHand, assembledHand);

    vector<Cards> temp = assembledHand->bestCombo;
    vector<vector<Cards>> ret;
    while (!temp.empty()) {
        ret.push_back(temp);
        assembledHand = assembledHand->bestChild;
        temp = assembledHand->bestCombo;
    }

    return ret;
}

string Player::getAssembledHandAsString() {
    vector<vector<Cards>> arrangedHand = assemblePossibleHand();
    string temp;
    for (auto const& eachHand : arrangedHand) {
        for (auto eachCard : eachHand) {
            temp += eachCard.toString() + " ";
        }
        temp += " | ";
    }
    return temp;
}

void Player::removeCards(vector<Cards> &a_hand, vector<Cards> cards) {
    for (auto const &each : cards) {
        for (int i = 0; i < a_hand.size(); i++) {
            if (each == a_hand[i]) {
                a_hand.erase(a_hand.begin() + i);
                break;
            }
        }
    }
}

int Player::getLowestScore(vector<Cards> &a_hand, Assembled *assembled_hands) {
    int minScore = 99999;

    vector<Cards> bestCombo;
    vector<Cards> t_hand = a_hand;
    sortCards(t_hand);
    vector<vector <Cards>> booksAndRuns = getBooksAndRuns(t_hand);

    // base case
    if (booksAndRuns.empty()) {
        Assembled *temp_assembled = new Assembled(t_hand);
        assembled_hands->bestChild = temp_assembled;
        assembled_hands->bestCombo = a_hand;
        return calculateRealScore(a_hand);
    }
    // generate child hands of each by removing the parent cards
    else {
        for (auto const each : booksAndRuns) {
            // copy the current hand
            vector <Cards> temp_hand = a_hand;

            // remove the books or runs from the hand
            removeCards(temp_hand, each);

            Assembled *temp_assembled = new Assembled(temp_hand);

            // calculate the score -> recursion
            int scr = getLowestScore(temp_hand, temp_assembled);

            // set the minScore of this parent
            // also set the best combo of this parent
            if (scr < minScore) {
                minScore = scr;
                assembled_hands->bestChild = temp_assembled;
                assembled_hands->bestCombo = each;
                bestCombo = each;
            }
        }

    }
    // push the best combination of this depth into the assembled hands vector
//    assembled_hands.push_back(bestCombo);

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

    for (auto const &e_suite : suite) {
        vector<Cards> curr;
        for (auto e_card : a_hand) {
            if (e_card.getSuite() == e_suite) {
                curr.push_back(e_card);
            }
        }
        if (curr.size() > 1){
            // add jokers and wildcards to that group
            for (auto const &each : jokers) {
                curr.push_back(each);
            }
            for (auto const &each : wilds) {
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
