//
// Created by bibhash on 9/29/19.
//

#include "Validate.hpp"
#include "Deck.hpp"

// checks if the cards have the same suite
bool Validate::hasSameSuite(vector<Cards> a_hand) {
    if (a_hand.empty()) return true;

    string a_suite = a_hand[0].getSuite();
    for (auto each : a_hand) {
        if (each.getSuite() != a_suite) {
            return false;
        }
    }
    return true;
}


// checks if the cards have the potential to be a run
bool Validate::canBeRun(vector<Cards> a_cards, int &missingCardsCount) {
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
        }
    }

    return true;
}


// checks if the cards can be arranged as a run
bool Validate::isRun(vector<Cards> a_hand) {
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

        // Step 2: sort the cards according to the face value
        // sort(initialHand.begin(), initialHand.end(), &Player::compareIntervalCards);
        sortCards(initialHand);

        int missingCardsCount = 0;

        // Step 3: compare each card and see if it can be a potential run
        // pass the missing Cards Count by reference to keep track of it
        bool potentialRun = canBeRun(initialHand, missingCardsCount);

        // Step 4: check the type of run
        // STEP 4.1: you reach this point if you need to consider joker and wildcards
        if (potentialRun && missingCardsCount <= (jokerCards.size() + wildCards.size())) {
            return true;
        }
    }

    return false;
}

// checks if the cards can be arranged as book
bool Validate::isBook(vector<Cards> a_hand) {
    if (a_hand.empty()){
        return true;
    }

    Deck* deck = &Deck::getInstanceOfDeck(2);
    string wildCard = deck->getWildCardFace();

    vector<Cards> initialHand = a_hand;
    vector<Cards> jokerCards = extractJokerCards(initialHand);
    vector<Cards> wildCards = extractWildCards(initialHand);

    for (int i = 0; i < initialHand.size() - 1; i++) {
        if (initialHand[i].getFaceValue() != initialHand[i+1].getFaceValue()) {
            return false;
        }
    }
    return true;
}


// checks the combination of cards in the passed hand and returns the score
int Validate::checkCombo(vector<Cards> permutedHands, vector<int> combos) {
    int score = 0;

    for (int i = 0; i < combos.size()-1; i++) {
        int start = combos[i];
        int end = combos[i+1];

        // take the combination from the hand
        vector<Cards> comboHand (permutedHands.begin()+start, permutedHands.begin()+end);

        // check for run or book for that combination of the hand
        if (!isRun(comboHand) && !isBook(comboHand)){
            // calculate the score of that combination and store it
            score += calculateScoreOfHand(comboHand);
        }
        if (combos.size() <= 2) {
            vector<Cards> cHand (permutedHands.begin()+end, permutedHands.end());
            score += calculateScoreOfHand(cHand);
        }
    }

    return score;
}

// this is called only when the hand is neither a run or a book
int Validate::calculateScoreOfHand(vector<Cards> a_hand) {
    int score = 0;

    Deck* deck = &Deck::getInstanceOfDeck(2);
    string wildCard = deck->getWildCardFace();

    for (auto each : a_hand) {
        int currCardVal;

        if (each.getFace() == wildCard) {
            currCardVal = 0;
        }
        else if (each.isJoker()) {
            currCardVal = 0;
        }
        else {
            currCardVal = each.getFaceValue();
        }

        score += currCardVal;
    }

    return score;
}

int Validate::calculateRealScore(vector<Cards> a_hand) {
    int score = 0;

    Deck* deck = &Deck::getInstanceOfDeck(2);
    string wildCard = deck->getWildCardFace();

    for (auto each : a_hand) {
        int currCardVal;

        if (each.getFace() == wildCard) {
            currCardVal = 20;
        }
        else if (each.isJoker()) {
            currCardVal = 50;
        }
        else {
            currCardVal = each.getFaceValue();
        }

        score += currCardVal;
    }

    return score;
}

vector<vector<int>> Validate::getCombinationIndices(int size) {
    vector<vector<int>> temp;
    switch (size){
        case 3:
            temp.push_back({0,3});
            break;

        case 4:
            temp.push_back({0,3});
            break;

        case 5:
            temp.push_back({0,3});
            break;

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

void Validate::permute(vector<Cards> a_hand, int left, int right, vector<vector<Cards>>& permuted) {
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

// sorts the vector of cards
void Validate::sortCards(vector<Cards> &a_hand) {
    for (int i = 0; i < a_hand.size(); i++) {
        for (int j = 0; j < a_hand.size() - i - 1; j++) {
            if (a_hand[j].getFaceValue() > a_hand[j + 1].getFaceValue()){
                swapCards(&a_hand[j], &a_hand[j+1]);
            }
        }
    }
}

// swaps two cards' pointer
void Validate::swapCards(Cards *left, Cards *right) {
    Cards temp = *left;
    *left = *right;
    *right = temp;
}

// extracts the joker from the hand argument passed and returns them
vector<Cards> Validate::extractJokerCards(vector<Cards> &hand) {
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
vector<Cards> Validate::extractWildCardsSameSuite(vector<Cards> &a_hand, string a_suite) {
    vector<Cards> temp;

    int handSize = a_hand.size();

    Deck* deck = &Deck::getInstanceOfDeck(2);
    string wildCard = deck->getWildCardFace();

    for (int i = 0; i < handSize; i++) {
        if (a_hand[i].getFace() == wildCard && a_hand[i].getSuite() == a_suite) {
            temp.push_back(a_hand[i]);
            a_hand.erase(a_hand.begin() + i);
        }
    }
    return temp;
}

vector<Cards> Validate::extractWildCardsDiffSuite(vector<Cards> &a_hand, string a_suite) {
    vector<Cards> temp;

    int handSize = a_hand.size();

    Deck* deck = &Deck::getInstanceOfDeck(2);
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
vector<Cards> Validate::extractWildCards(vector<Cards> &a_hand) {
    vector<Cards> temp;

    int handSize = a_hand.size();

    Deck* deck = &Deck::getInstanceOfDeck(2);
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

