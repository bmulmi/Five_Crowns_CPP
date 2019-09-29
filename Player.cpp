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

// checks the combination of cards in the passed hand
bool Player::checkCombo(vector<Cards> permutedHands, vector<int> combos) {

    for (int i = 0; i < combos.size()-1; i++) {
        int start = combos[i];
        int end = combos[i+1];

        // take the combination from the hand
        vector<Cards> comboHand (permutedHands.begin()+start, permutedHands.begin()+end);

        // check for run or book for that combination of the hand
        if (!isRun(comboHand) || !isBook(comboHand)){
            // try another combination of hand
            return false;
        }
    }
    return true;
}

vector<vector<int>> Player::getCombinationIndices(int size) {
    vector<vector<int>> temp;
    switch (size){
        case 6:
            temp.push_back({0,6});
            temp.push_back({0,3,6});
            break;

        case 7:
            temp.push_back({0,7});
            temp.push_back({0,3,7});
            break;

        case 8:
            temp.push_back({0,8});
            temp.push_back({0,3,8});
            temp.push_back({0,4,8});
            break;

        case 9:
            temp.push_back({0,9});
            temp.push_back({0,3,9});
            temp.push_back({0,4,9});
            temp.push_back({0,3,6,9});
            break;

        case 10:
            temp.push_back({0,10});
            temp.push_back({0,3,10});
            temp.push_back({0,4,10});
            temp.push_back({0,5,10});
            temp.push_back({0,3,6,10});
            break;

        // TODO: check the following
        case 11:
            temp.push_back({0,11});
            temp.push_back({0,3,11});
            temp.push_back({0,4,11});
            temp.push_back({0,5,11});
            temp.push_back({0,3,6,11});
            temp.push_back({0,3,7,11});
            break;

        case 12:
            temp.push_back({0,12});
            temp.push_back({0,3,12});
            temp.push_back({0,4,12});
            temp.push_back({0,5,12});
            temp.push_back({0,6,12});
            temp.push_back({0,3,6,12});
            temp.push_back({0,3,7,12});
            temp.push_back({0,4,8,12});
            temp.push_back({0,3,6,9,12});
            break;

        case 13:
            temp.push_back({0,13});
            temp.push_back({0,3,13});
            temp.push_back({0,4,13});
            temp.push_back({0,5,13});
            temp.push_back({0,6,13});
            temp.push_back({0,3,6,13});
            temp.push_back({0,3,7,13});
            temp.push_back({0,3,8,13});
            temp.push_back({0,4,8,13});
            temp.push_back({0,3,6,9,13});
            break;

        default:
            break;
    }
    return temp;
}

void Player::permute(vector<Cards> a_hand, int left, int right, vector<vector<Cards>>& permuted) {
    if (left == right) {
        permuted.push_back(a_hand);
    }
    else {
        for (int i = left; i <= right; i++) {
            swapCards(&a_hand[left], &a_hand[i]);
            permute(a_hand, left+1, right, permuted);
            swapCards(&a_hand[left], &a_hand[i]);
        }
    }
}

// extracts the joker from the hand argument passed and returns them
vector<Cards> Player::extractJokerCards(vector<Cards> &hand) {
    vector<Cards> temp;
    int handSize = hand.size();

    for (int i = 0; i < handSize; i++) {
        if (hand[i].isJoker()) {
            temp.push_back(hand[i]);
            hand.erase(hand.begin() + i);
            i--;
            handSize--;
        }
    }
    return temp;
}

// removes the wild card from the hand passed in and returns the wild cards
vector<Cards> Player::extractWildCardsSameSuite(vector<Cards> &a_hand, string a_suite) {
    vector<Cards> temp;

    int handSize = a_hand.size();

    deck = &Deck::getInstanceOfDeck(2);
    string wildCard = deck->getWildCardFace();

    for (int i = 0; i < handSize; i++) {
        if (a_hand[i].getFace() == wildCard && a_hand[i].getSuite() == a_suite) {
            temp.push_back(a_hand[i]);
            a_hand.erase(a_hand.begin() + i);
        }
    }
    return temp;
}

vector<Cards> Player::extractWildCardsDiffSuite(vector<Cards> &a_hand, string a_suite) {
    vector<Cards> temp;

    int handSize = a_hand.size();

    deck = &Deck::getInstanceOfDeck(2);
    string wildCard = deck->getWildCardFace();

    for (int i = 0; i < handSize; i++) {
        if (a_hand[i].getFace() == wildCard && a_hand[i].getSuite() != a_suite) {
            temp.push_back(a_hand[i]);
            a_hand.erase(a_hand.begin() + i);
        }
    }
    return temp;
}

// extracts all the wild cards from the hand
vector<Cards> Player::extractWildCards(vector<Cards> &a_hand) {
    vector<Cards> temp;

    int handSize = a_hand.size();

    deck = &Deck::getInstanceOfDeck(2);
    string wildCard = deck->getWildCardFace();

    for (int i = 0; i < handSize; i++) {
        if (a_hand[i].getFace() == wildCard) {
            temp.push_back(a_hand[i]);
            a_hand.erase(a_hand.begin() + i);
            i--;
            handSize--;
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

bool Player::canBeRun(vector<Cards> a_cards, int &missingCardsCount) {
    bool isMissingCards = false;
    for (int i = 0; i < a_cards.size() - 1; i++) {
        // Step 3.1: check if each card's face is equal to the face value of the next card minus one
        if (a_cards[i].getFaceValue() == a_cards[i + 1].getFaceValue() - 1) {
            continue;
        }
        // Step 3.2: check if there are two same face cards
        if (a_cards[i].getFaceValue() == a_cards[i + 1].getFaceValue()) {
            return false;
        }
        // Step 3.3: you reach this point if one or more cards are missing in between the run
        if (a_cards[i].getFaceValue() < a_cards[i + 1].getFaceValue()) {
            // add the count of missing cards in between runs
            missingCardsCount += a_cards[i + 1].getFaceValue() - a_cards[i].getFaceValue() - 1;
            isMissingCards = true;
        }
    }

    if (isMissingCards) {
        return true;
    }
}

// checks if the cards can be arranged as a run
bool Player::isRun(vector<Cards> a_hand) {
    if (a_hand.empty()) {
        return true;
    }

    vector<Cards> initialHand = a_hand;
    vector<Cards> jokerCards = extractJokerCards(initialHand);
    vector<Cards> wildCards = extractWildCards(initialHand);

    // Step 1: all suites of the hand must be the same for runs
    if (hasSameSuite(initialHand)) {
        // store the suite of this hand
        string suite = initialHand[0].getSuite();

        // store the wildcards with same suite of the hand
        // vector<Cards> sameSuiteWilds = extractWildCardsSameSuite(initialHand, suite);

        // store the wildcards with different suite of the hand
        // vector<Cards> diffSuiteWilds = extractWildCardsDiffSuite(initialHand, suite);

        // Step 2: sort the cards according to the face value
        // sort(initialHand.begin(), initialHand.end(), &Player::compareIntervalCards);
        sortCards(initialHand);

        int missingCardsCount = 0;

        // Step 3: compare each card and see if it can be a potential run
        // pass the missing Cards Count by reference to keep track of it
        bool potentialRun = canBeRun(initialHand, missingCardsCount);

        // Step 4: you reach this point if you need to consider joker and wildcards
        if (potentialRun && (jokerCards.size() + wildCards.size()) <= missingCardsCount) {
            // when missing Cards are less than the total jokers and wild cards
            // return true
            return true;
                // get same suite wild card
//                Cards temp = sameSuiteWilds.back();
//                sameSuiteWilds.pop_back();
//                // push it in the initial hand
//                initialHand.push_back(temp);
//                // sort the hand
//                sortCards(initialHand);
//                // check for potential run
//                int tempMissCards = 0;
//                bool tempRun = canBeRun(initialHand, tempMissCards);
        }
    }
    // all else cases return false
    return false;
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
    vector<Cards> jokerCards = extractJokerCards(initialHand);
    vector<Cards> wildCards = extractWildCards(initialHand);
    for (int i = 0; i < initialHand.size(); i++) {
        if (initialHand[0].getFaceValue() != initialHand[i].getFaceValue()) {
            return false;
        }
    }

    return true;
}