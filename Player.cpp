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

Player::~Player() {

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
    if ((currHand.size() < 6) && (isRun(currHand) ||  isBook(currHand))) {
        return true;
    }
    else {

    }
}

// extracts the joker from the hand argument passed and returns them
vector<Cards> Player::extractJokerAndWildCards(vector<Cards> &hand) {
    vector<Cards> temp;
    int handSize = hand.size();
    Deck* deck = &Deck::getInstanceOfDeck(2);
    string wildCard = deck->getWildCardFace();

    for (int i = 0; i < handSize; i++) {
        if (hand[i].isJoker() || hand[i].getFace() == wildCard) {
            temp.push_back(hand[i]);
            hand.erase(hand.begin() + i);
        }
    }
    return temp;
}

// checks if the cards have the same suite
bool Player::hasSameSuite(vector<Cards> a_hand) {
    if (a_hand.empty()) return true;

    string a_suite = a_hand[0].getSuite();
    for (auto each : a_hand) {
        if (each.getSuite() != a_suite) {
            return false;
        }
    }
    return true;
}

// checks if the cards can be arranged as a run
bool Player::isRun(vector<Cards> a_hand) {
    if (a_hand.empty()) {
        return true;
    }

    vector<Cards> initialHand = a_hand;
    vector<Cards> jokersAndWilds = extractJokerAndWildCards(initialHand);
    // Step 1: all suites of the hand must be the same for runs
    if (hasSameSuite(initialHand)) {
        // Step 2: sort the cards according to the face value
        // sort(initialHand.begin(), initialHand.end(), &Player::compareIntervalCards);
        sortCards(initialHand);

        int missingCardsCount = 0;
        bool requiresJokersAndWilds = false;

        // Step 3: compare each card
        for (int i = 0; i < initialHand.size() - 1; i++) {
            // Step 3.1: check if each card's face is equal to the face value of the next card minus one
            if (initialHand[i].getFaceValue() == initialHand[i + 1].getFaceValue() - 1) {
                continue;
            }
            // Step 3.2: check if there are two same face cards
            if (initialHand[i].getFaceValue() == initialHand[i + 1].getFaceValue()) {
                return false;
            }
            // Step 3.3: you reach this point if one or more cards are missing in between the run
            if (initialHand[i].getFaceValue() < initialHand[i + 1].getFaceValue()) {
                // add the count of missing cards in between runs
                missingCardsCount += initialHand[i + 1].getFaceValue() - initialHand[i].getFaceValue() - 1;
                requiresJokersAndWilds = true;
            }
        }
        // Step 4: you reach this point if you need to consider joker or if it is a perfect run
        if (requiresJokersAndWilds) {
            return jokersAndWilds.size() == missingCardsCount;
        }
        else {
            return true;
        }
    }
    else {
        return false;
    }
}

bool Player::compareIntervalCards(Cards left, Cards right) {
    return left.getFaceValue() < right.getFaceValue();
}

// sorts the vector of cards
void Player::sortCards(vector<Cards> &a_hand) {
    for (int i = 0; i < a_hand.size(); i++) {
        for (int j = 0; j < a_hand.size() - i - 1; j++) {
            if (a_hand[j].getFaceValue() > a_hand[j + 1].getFaceValue()){
                swapCards(&a_hand[j], &a_hand[j+1]);
            }
        }
    }
}

// swaps two cards' pointer
void Player::swapCards(Cards *left, Cards *right) {
    Cards temp = *left;
    *left = *right;
    *right = temp;
}

// checks if the cards can be arranged as book
bool Player::isBook(vector<Cards> a_hand) {
    if (a_hand.empty()){
        return true;
    }

    vector<Cards> initialHand = a_hand;
    vector<Cards> jokersAndWilds = extractJokerAndWildCards(initialHand);
    for (int i = 0; i < initialHand.size(); i++) {
        if (initialHand[0].getFaceValue() != initialHand[i].getFaceValue()) {
            return false;
        }
    }

    return true;
}