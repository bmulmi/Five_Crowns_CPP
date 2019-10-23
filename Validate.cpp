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
 * Function Name: isRun
 * Purpose: To check if a vector of Cards is a run
 * Parameters:
 *          a_hand, a vector of Cards. It holds the cards to be checked
 *          for run.
 * Return Value: Boolean
 * Local Variables:
 *          initialHand, a vector of Cards object. It holds the copy of
 *          hand
 *
 *          jokerCards, a vector of Cards object. It holds the jokers
 *          from the hand.
 *
 *          wildCards, a vector of Cards object. It holds the wild cards
 *          from the hand.
 *
 *          suite, a string value. It holds the suite of a card.
 *
 *          missingCardsCount, an int value. It holds the number of cards
 *          missing between two cards which may be replaced by a joker or
 *          a wild card.
 *
 *          potentialRun, a boolean value. It store boolean value for the
 *          hand that can possibly be a run if jokers and wild cards are used.
 * Algorithm:
 *               1) Make copy of the hand passed. Return false if hand size is
 *                  less than 3.
 *               2) Extract jokers and wild cards from it and store them.
 *               3) Check if the copied hand is empty after extraction. Return
 *                  true if yes. Else, continue.
 *               4) Check if the hand cards have same suite, if not return false.
 *               5) Check if the hand can be a potential run.
 *               6) If missingCardsCount is less than or equal to total number of
 *                  special cards and the hand can potentially be a run, return true.
 *               7) Else, return false.
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
 * Function Name: isBook
 * Purpose: To Check if the vector of cards is a book
 * Parameters:
 *          a_hand, a vector of Cards. It holds the cards to be checked for
 *          books.
 * Return Value: Boolean
 * Local Variables:
 *          wildCard, a string value that holds the face of wild card
 *
 *          initialHand, a vector of Cards that holds the copy of hand.
 *
 *          jokerCards, a vector of Cards object. It holds the jokers
 *          from the hand.
 *
 *          wildCards, a vector of Cards object. It holds the wild cards
 *          from the hand.
 * Algorithm:
 *               1) If hand size is less than 3 return false.
 *               2) Make a copy of the vector of cards, extract wild cards
 *                  and jokers from it and store them.
 *               3) Return true if the copied hand is empty.
 *               4) For each card in hand, check if their face value match
 *                  each other. If not, return false.
 *               5) Else return true.
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
 * Function Name: hasSameSuite
 * Purpose: To check if vector of cards are of same suite
 * Parameters:
 *          a_hand, a vector of Cards object. It holds the cards to be checked
 * Return Value: Boolean
 * Local Variables:
 *          a_suite, a string value. It holds the suite of one of the cards.
 * Algorithm:
 *               1) Get the suite of one of the cards in hand.
 *               2) For each card in hand, check if the suites are same.
 *               3) Return false if not same, return true otherwise.
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
 * Function Name: canBeRun
 * Purpose: To check if the vector of cards have potential to become a run
 * Parameters:
 *          a_cards, the vector of Cards object. It holds the cards to be
 *          checked.
 *
 *          missingCardsCount, an int value. It holds the number of missing
 *          cards for creating a run from this hand.
 * Return Value: Boolean
 * Local Variables:
 *          None
 * Algorithm:
 *               1) For every card in the hand, Check:
 *                  a) if the face value of next card is one greater, continue.
 *                  b) if the face value of next card is same, return false.
 *                  c) if the face value of next card is greater.
 *                      i. get the amount by which it is greater and
 *                          add it to the missingCardsCount.
 *               2) Return true.
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
 * Function Name: calculateScore
 * Purpose: To calculate score of the hand
 * Parameters:
 *          a_hand, a vector of Cards object. It holds the cards form the
 *          player's hand.
 * Return Value: an int value which is the score of hand
 * Local Variables:
 *          wildCard, a string representation of the wild card.
 *
 *          currCardVal, an int value that holds the current face value
 *          of the card of hand.
 *
 *          score, an int value that holds the score of the hand.
 * Algorithm:
 *               1) For each card in hand, get the face value and add
 *                  it to the score. If it is a special card, get it's
 *                  value and add it to the score.
 *               2) Return the score.
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
 * Function Name: sortCards
 * Purpose: To sort the cards of hand
 * Parameters:
 *          a_hand, a vector of Cards object passed by reference. The hand
 *          will be sorted after this.
 * Return Value: None
 * Local Variables:
 *          None
 * Algorithm:
 *               1) Perform a bubble sort on the hand passed
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
 * Function Name: swapCards
 * Purpose: To swap two cards
 * Parameters:
 *          left, a pointer to Cards object.
 *          right, a pointer to Cards object.
 * Return Value: None
 * Local Variables:
 *          temp, a pointer to Cards object that stores one of the passed
 *          pointers for swapping.
 * Algorithm:
 *               1) Store the left pointer to temp.
 *               2) Assign the left pointer to right.
 *               3) Assign the right pointer to temp.
 * Assistance Received: None
 **********************************************************************/
// swaps two cards' pointer
void Validate::swapCards(Cards *left, Cards *right) {
    Cards temp = *left;
    *left = *right;
    *right = temp;
}

/**********************************************************************
 * Function Name: extractJokerCards
 * Purpose: To remove Jokers from hand and return them
 * Parameters:
 *          hand, a vector of Cards. It holds the cards of player's hand.
 * Return Value: Joker cards as vector of cards
 * Local Variables:
 *          temp, a vector of cards that holds the extracted joker cards
 * Algorithm:
 *               1) For each card in hand, add it to temp and erase it
 *                  from the hand if it is a joker.
 *               2) Return the temp vector.
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
 * Function Name: extractWildCards
 * Purpose: To extract wild cards from hand and return them
 * Parameters:
 *          a_hand, a vector of Cards object. It holds the cards of player's
 *          hand.
 * Return Value: Wild cards as vector of cards
 * Local Variables:
 *          temp, a vector of Cards. It holds the wild cards extracted
 *          from the hand
 *
 *          handSize, an int value. It holds the size of the hand.
 *
 *          wildCard, a string value. It holds the face of wild card.
 * Algorithm:
 *               1) For every card in hand, push it to temp vector and
 *                  remove it from the hand if it's face value matches
 *                  to that of the wild card.
 *               2) Return the temp vector.
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
