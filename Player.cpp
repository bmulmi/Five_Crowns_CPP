/*
 ************************************************************
 * Name: Bibhash Mulmi                                      *
 * Project: P1 Five Crowns CPP                              *
 * Class: OPL Fall 19                                       *
 * Date: 10/23/2019                                         *
 ************************************************************
*/

// Created by bibhash on 9/11/19.


#include "Player.hpp"

Player::Player() {
    score = 0;
    goneOut = false;
    saveGame = false;
    quitGame = false;
    hand.clear();
}

/**********************************************************************
 * Function Name: getHandAsString
 * Purpose:  To get the string representation of hand
 * Parameters:
 *              None
 * Return Value: a string value. It holds the string representation of 
                hand
 * Local Variables:
 *              temp, a string value. It holds the string representation of 
 *              hand
 * Assistance Received: None
 **********************************************************************/
string Player::getHandAsString() {
    string temp = "";

    for (auto a_card : this->hand) {
        temp += a_card.toString() + " ";
    }

    return temp;
}

/**********************************************************************
 * Function Name: getAssembledHandAsString
 * Purpose: To get the assembled hand as string
 * Parameters:
 *              None
 * Return Value: a string representation of arranged hand
 * Local Variables:
 *              arrangedHand, a vector of vector of Cards object. It holds
 *              the assembled runs and books and remaining cards in a string.
 * Assistance Received: None
 **********************************************************************/
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

/**********************************************************************
 * Function Name: getCardIndex
 * Purpose: To get the index of card in hand
 * Parameters:
 *              a_hand, a vector of Cards object. It represents the hand.
 *              a_card, a Cards object. It represents the card to find the
 *              index of.
 * Return Value: an int value representing the index of card.
 * Local Variables:
 *              None
 * Algorithm:
 *               1) For each card in hand, compare it with the card passed,
 *                  if it matches, return the index, else return -1.
 * Assistance Received: None
 **********************************************************************/
int Player::getCardIndex(vector<Cards> a_hand, Cards a_card) const {
    for (int i = 0; i < a_hand.size(); i++) {
        if (a_hand[i] == a_card) {
            return i;
        }
    }
    return -1;
}

/**********************************************************************
 * Function Name: getHandScore
 * Purpose: To get the score of the current hand
 * Parameters:
 *              None
 * Return Value: an int value that holds the score of the hand
 * Local Variables:
 *              possibleCombos, a vector of vector of Cards object. It holds
 *              the combinations of runs and books of the hand.
 *              
 *              scoreHand, a vector of Cards object. It holds the last vector
 *              of possibleCombos. This combination is the remaining unaccounted
 *              cards of the hand.
 *              
 *              currScore, an int value. It holds the score of the scoreHand.
 * Algorithm:
 *               1) If the hand can go out, return 0.
 *               2) Get the assembled hand, get the last combination from it.
 *               3) Calculate the score of the last combination and return it.
 * Assistance Received: None
 **********************************************************************/
int Player::getHandScore() {
    if (canGoOut(hand)) {
        return 0;
    }

    vector<vector<Cards>> possibleCombos = assemblePossibleHand();

    // the unaccounted cards are at the back of the assembled hand.
    vector<Cards> scoreHand = possibleCombos.back();

    int currScore = calculateScore(scoreHand);
    return currScore;
}

/**********************************************************************
 * Function Name: removeCards
 * Purpose: To remove the card from hand
 * Parameters:
 *              a_hand, a vector of Cards object passed by reference. The
 *              hand is changed since we are removing a card from it.
 *              cards, a vector of Cards object that needs to be removed 
 *              from a_hand.
 * Return Value: None
 * Local Variables:
 *              None
 * Algorithm:
 *               1) For each card in cards, compare each card in hand, and
 *                  when matched, remove the card from hand.
 * Assistance Received: None
 **********************************************************************/
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

/**********************************************************************
 * Function Name: canGoOut
 * Purpose: To check if the player can go out
 * Parameters:
 *              a_hand, a vector of Cards object. It holds the hand of 
 *              the player
 * Return Value: a boolean value. True if player can go out, false otherwise.
 * Local Variables:
 *              *assembledHands, a pointer to Assembled object/struct. 
 *              temp, an int value, it holds the score of the player's hand.
 * Algorithm:
 *               1) Get the lowest score of hand. Return true if it is 0, else
 *                  false.
 * Assistance Received: None
 **********************************************************************/
// checks to see if the player can go out or not
bool Player::canGoOut(vector<Cards> a_hand) {
    Assembled *assembledHands = new Assembled(hand);
    int temp = getLowestScore(a_hand, assembledHands);
    return temp == 0;
}

/**********************************************************************
 * Function Name: whichPileToChoose
 * Purpose: To get the pile to pick card from by using computer's strategy.
 * Parameters: 
 *              None
 * Return Value: a string value representing the pile name.
 * Local Variables:
 *              pickedCard, a Cards object. It holds the top discard pile
 *              card.
 *
 *              wildCard, a string value. It holds the face of wild card.
 *
 *              copyHand, a vector of Cards object. It holds a copy of the
 *              player's hand.
 *
 *              assembledHand, a pointer to Assembled struct for the copy
 *              hand. 
 * Algorithm:
 *               1) Make a copy of the current hand and add the discard pile
 *                  card to it. Initialize assembledHand and score of original hand.
 *               2) Remove each card from the copied hand and keep track of score of
 *                  each temp hand.
 *               3) If the the assembled hand of the temp hand has more combinations
 *                  and the score of the hand is less than the current score of hand,
 *                  set the assembledHand and score to that of temp hand. Put a flag
 *                  to choose from discard pile. Return discard pile.
 *               4) Else, return draw pile.  
 * Assistance Received: None
 **********************************************************************/
string Player::whichPileToChoose() {
    deck = &Deck::getInstanceOfDeck(2);

    // take the discard pile card
    Cards pickedCard = deck->showDiscardCard();

    string wildCard = deck->getWildCardFace();

    vector<Cards> copyHand = hand;

    Assembled *assembledHand = new Assembled(copyHand);
    // store the score of hand before picking discard card
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

/**********************************************************************
 * Function Name: whichCardToDiscard
 * Purpose: To get the index of card to discard from the current hand using
 *          computer's strategy.
 * Parameters: 
 *              None
 * Return Value: an int value that holds the index of the discarding card of hand  
 * Local Variables:
 *              currHand, a vector of Cards object that holds the copy of player's
 *              current hand.
 *
 *              cardIndex, an int value. It holds the index of the card to discard.
 *
 *              currScore, an int value. It holds the lowest possible score of the 
 *              hand.
 *
 *              wildCard, a string value. It holds the face of wild card.
 *
 *              temp, a vector of Cards object. It holds the copy of currHand. Cards
 *              are erased from this copy to get the lowest score of hand.
 * Algorithm:
 *               1) Initialize cardIndex, currScore, wildCard values. 
 *               2) Copy the current hand and remove each card and check the score.
 *               3) If the score is lower than currScore, update the cardIndex to 
 *                  current index and currScore to current score.
 *               4) Return the card index.
 * Assistance Received: None
 **********************************************************************/
int Player::whichCardToDiscard() {
    vector<Cards> currHand = hand;
    int cardIndex = 0;
    int currScore = 99999;

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

        Assembled *assembledHand = new Assembled(temp);
        // now count the score;
        int tempScr = getLowestScore(temp, assembledHand);
        if (tempScr < currScore) {
            currScore = tempScr;
            cardIndex = i;
        }
    }
    return cardIndex;
}

/**********************************************************************
 * Function Name: assemblePossibleHand
 * Purpose: To assemble possible runs and books from the current hand
 * Parameters:
 *              None
 * Return Value: None
 * Local Variables:
 *              currHand, a vector of Cards object. It holds a copy of the
 *              player's hand.
 *
 *              assembledHand, a pointer to Assembled struct. It holds the
 *              assembled combinations of books and runs.
 *
 *              scr, an int value. It holds the score of current hand.
 *
 *              temp, a vector of Cards object. It holds the best combo
 *              of the assembled hand struct
 *
 *              ret, a vector of vector of Cards object. It holds the 
 *              runs and books.
 *
 *              isSpecial, a boolean flag that keeps track of the last 
 *              combination of assembled hand whether it is a run or a book.
 *
 *              lastCombo, a vector of Cards object that holds the last 
 *              combination of assembled hand.
 * Algorithm:
 *               1) Initialize assembled hand, current hand, score, returning vector
 *               2) Pass the assembled hand into getLowestScore function. This function
 *                  adds the combinations into the struct.
 *               3) Store each combination from the struct into ret vector.
 *               3) Check whether the last combination in the vector is all 
 *                  wild cards or jokers. If true, push every card into the second last
 *                  combination of ret vector.
 *               4) Return the ret vector.
 * Assistance Received: None
 **********************************************************************/
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

    bool isSpecial = true;
    vector<Cards> lastCombo = ret.back();
    deck = &Deck::getInstanceOfDeck(2);

    // check whether the last combo contains all jokers or wild cards
    for (auto each : lastCombo) {
        if (!each.isJoker() && each.getFace() != deck->getWildCardFace()) {
            isSpecial = false;
        }
    }

    if (isSpecial) {
        // the last combo contains special cards only
        // remove the combo and combine it with the second last combo
        ret.pop_back();
        for (auto const &each : lastCombo) {
            ret.back().push_back(each);
        }
    }

    return ret;
}

/**********************************************************************
 * Function Name: getLowestScore
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
        return calculateScore(a_hand);
    }
    // generate child hands of each by removing the books and runs from the parent's cards
    else {
        for (auto const each : booksAndRuns) {
            // copy the current hand
            vector <Cards> temp_hand = a_hand;

            removeCards(temp_hand, each);

            Assembled *temp_assembled = new Assembled(temp_hand);

            // calculate the score -> recursion
            int scr = getLowestScore(temp_hand, temp_assembled);

            if (scr < minScore) {
                // set the minScore of this parent
                // also set the best combo of this parent
                minScore = scr;
                assembled_hands->bestChild = temp_assembled;
                assembled_hands->bestCombo = each;
                bestCombo = each;
            }
        }

    }

    return minScore;
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

    // STEP 1: check without jokers and wilds
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
void Player::combineAndCheck(vector <Cards> a_hand, vector <Cards> a_cards, vector <vector<Cards>> &collection, int check_type) {
    for (int i = 0; i < a_hand.size(); i++) {
        for (int j = 0; j < a_hand.size() + 1 - i; j++) {
            // generate the combination
            vector<Cards> curr (a_hand.begin()+i, a_hand.begin()+i+j);

            vector<Cards> cardsToCombine = a_cards;
            // check this group of cards with special cards
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
void Player::combineTwoAndCheck(vector<Cards> a_hand, vector<Cards> a_cards1, vector<Cards> a_cards2,
                                vector<vector<Cards>> &collection, int check_type) {
    for (int i = 0; i < a_hand.size(); i++) {
        for (int j = 0; j < a_hand.size() + 1 - i; j++) {
            // generate the combination
            vector<Cards> curr (a_hand.begin()+i, a_hand.begin()+i+j);
            vector<Cards> temp_cards1 = a_cards1;

            // check this group of cards with wild cards for runs or books
            while (!temp_cards1.empty()) {
                Cards currWilds = temp_cards1.back();
                temp_cards1.pop_back();
                curr.push_back(currWilds);

                // make a copy of the cards
                vector<Cards> copy_curr = curr;

                vector<Cards> temp_cards2 = a_cards2;

                // push each joker to the copied hand and check runs or books
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
