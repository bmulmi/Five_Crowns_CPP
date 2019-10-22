/*
 ************************************************************
 * Name: Bibhash Mulmi                                      *
 * Project: P1 Five Crowns CPP                              *
 * Class: OPL Fall 19                                       *
 * Date: 10/23/2019                                         *
 ************************************************************
*/

// Created by bibhash on 9/29/19.


#include "Validate.hpp"
#include "Deck.hpp"

/**********************************************************************
 * Function Name:
 * Purpose:
 * Parameters:
 *
 * Return Value:
 * Local Variables:
 *
 * Algorithm:
 *               1)
 * Assistance Received: None
 **********************************************************************/
// checks if the cards can be arranged as a run
bool Validate::isRun(vector<Cards> a_hand) {
    if (a_hand.size() < 3) {
        return false;
    }

    vector<Cards> initialHand = a_hand;
    vector<Cards> jokerCards = extractJokerCards(initialHand);
    vector<Cards> wildCards = extractWildCards(initialHand);

    // if all the cards in hand is joker or wild cards
    if (initialHand.empty()){
        return true;
    }

    // Step 1: all suites of the hand must be the same for runs
    if (hasSameSuite(initialHand)) {
        // store the suite of this hand
        string suite = initialHand[0].getSuite();

        // Step 2: sort the cards according to the face value
        sortCards(initialHand);

        int missingCardsCount = 0;

        // Step 3: compare each card and see if it can be a potential run
        // pass the missing Cards Count by reference to keep track of it
        bool potentialRun = canBeRun(initialHand, missingCardsCount);

        // STEP 4: you reach this point if you need to consider joker and wildcards
        if (potentialRun && missingCardsCount <= (jokerCards.size() + wildCards.size())) {
            return true;
        }
    }

    return false;
}

/**********************************************************************
 * Function Name:
 * Purpose:
 * Parameters:
 *
 * Return Value:
 * Local Variables:
 *
 * Algorithm:
 *               1)
 * Assistance Received: None
 **********************************************************************/
// checks if the cards can be arranged as book
bool Validate::isBook(vector<Cards> a_hand) {
    if (a_hand.size() < 3) {
        return false;
    }

    Deck* deck = &Deck::getInstanceOfDeck(2);
    string wildCard = deck->getWildCardFace();

    vector<Cards> initialHand = a_hand;
    vector<Cards> jokerCards = extractJokerCards(initialHand);
    vector<Cards> wildCards = extractWildCards(initialHand);

    // if all the cards in hand is jokers and wild cards
    if ((initialHand.empty())){
        return true;
    }

    for (int i = 0; i < initialHand.size() - 1; i++) {
        if (initialHand[i].getFaceValue() != initialHand[i+1].getFaceValue()) {
            return false;
        }
    }

    return true;
}

/**********************************************************************
 * Function Name:
 * Purpose:
 * Parameters:
 *
 * Return Value:
 * Local Variables:
 *
 * Algorithm:
 *               1)
 * Assistance Received: None
 **********************************************************************/
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

/**********************************************************************
 * Function Name:
 * Purpose:
 * Parameters:
 *
 * Return Value:
 * Local Variables:
 *
 * Algorithm:
 *               1)
 * Assistance Received: None
 **********************************************************************/
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

/**********************************************************************
 * Function Name:
 * Purpose:
 * Parameters:
 *
 * Return Value:
 * Local Variables:
 *
 * Algorithm:
 *               1)
 * Assistance Received: None
 **********************************************************************/
int Validate::calculateScore(vector<Cards> a_hand) {
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

/**********************************************************************
 * Function Name:
 * Purpose:
 * Parameters:
 *
 * Return Value:
 * Local Variables:
 *
 * Algorithm:
 *               1)
 * Assistance Received: None
 **********************************************************************/
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

/**********************************************************************
 * Function Name:
 * Purpose:
 * Parameters:
 *
 * Return Value:
 * Local Variables:
 *
 * Algorithm:
 *               1)
 * Assistance Received: None
 **********************************************************************/
// swaps two cards' pointer
void Validate::swapCards(Cards *left, Cards *right) {
    Cards temp = *left;
    *left = *right;
    *right = temp;
}

/**********************************************************************
 * Function Name:
 * Purpose:
 * Parameters:
 *
 * Return Value:
 * Local Variables:
 *
 * Algorithm:
 *               1)
 * Assistance Received: None
 **********************************************************************/
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

/**********************************************************************
 * Function Name:
 * Purpose:
 * Parameters:
 *
 * Return Value:
 * Local Variables:
 *
 * Algorithm:
 *               1)
 * Assistance Received: None
 **********************************************************************/
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
