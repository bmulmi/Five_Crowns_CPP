/*
 ************************************************************
 * Name: Bibhash Mulmi                                      *
 * Project: P1 Five Crowns CPP                              *
 * Class: OPL Fall 19                                       *
 * Date: 10/23/2019                                         *
 ************************************************************
*/

// Created by bibhash on 9/10/19.


#include "Deck.hpp"
#include <bits/stdc++.h>
using namespace std;

Deck* Deck::deck = NULL;
deque<Cards> Deck::drawPile;
deque<Cards> Deck::discardPile;

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
Deck::Deck(int numDecks) {
    // create an initial deck of size numDecks
    deque<Cards> initialDeck = arrangeDeck(numDecks);
    drawPile = initialDeck;
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
Deck& Deck::getInstanceOfDeck(int num) {
    if (deck == nullptr){
        deck = new Deck(num);
    }
    return *deck;
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
// creates one deck of cards with Jokers
deque<Cards> Deck::createDeck() {
    deque<Cards> temp;

    for (auto a_suite : suite) {
        for (auto a_face : face) {
            temp.emplace_back(Cards(a_face, a_suite));
        }
    }

    for (auto const& joker : createJokers(numberOfJokers)) {
        temp.push_back(joker);
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
// arranges the number of decks into one deck
deque<Cards> Deck::arrangeDeck(int numDecks) {
    deque<Cards> initialDeck;

    for (int i = 0; i < numDecks; i++) {
        deque<Cards> secondaryDeck = createDeck();
        // push each card into the initial deck
        for (auto const &a_card : secondaryDeck) {
            initialDeck.push_back(a_card);
        }
    }

    return initialDeck;
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
// creates a deque of Jokers
deque<Cards> Deck::createJokers(int num) {
    deque<Cards> temp;
    string J_face = "J";

    for (int i = 1; i <= num; i++) {
        string J_suite = to_string(i);
        temp.emplace_back(Cards(J_face, J_suite));
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
// mixes the discard pile into draw pile and shuffles the deck
void Deck::shuffleDeck() {
    // initialize the seed
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();

    // clear both the piles
    drawPile.clear();
    discardPile.clear();

    // arrange the draw pile
    drawPile = arrangeDeck(2);

    // shuffle the draw pile
    shuffle(drawPile.begin(), drawPile.end(), default_random_engine(seed));
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
// returns top card of the draw pile and pops it from the pile
Cards Deck::drawCard() {
    Cards temp = drawPile.front();
    drawPile.pop_front();
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
// pushes card into top of discard pile
void Deck::discard(Cards a_card) {
    this->discardPile.push_front(a_card);
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
// returns top card of the discard pile
Cards Deck::showDiscardCard() {
    return discardPile.front();
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
// returns top card of the discard pile and pops it from the pile
Cards Deck::drawDiscardCard() {
    Cards temp = discardPile.front();
    discardPile.pop_front();
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
string Deck::getDiscardPile() {
    string temp;

    for (auto each : discardPile) {
        temp += each.toString() + " ";
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
string Deck::getDrawPile() {
    string temp;

    for (auto each : drawPile) {
        temp += each.toString() + " ";
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
void Deck::setDiscardPile(deque<Cards> cards) {
    discardPile.clear();
    discardPile = cards;
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
void Deck::setDrawPile(deque<Cards> cards) {
    drawPile.clear();
    drawPile = cards;
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
void Deck::setWildCard(int faceValue) {
    int tempFace = faceValue;

    if (tempFace > 9) {
        switch (tempFace) {
            case 10:
                this->wildCardFace = "X";
                break;

            case 11:
                this->wildCardFace = "J";
                break;

            case 12:
                this->wildCardFace = "Q";
                break;

            case 13:
                this->wildCardFace = "K";
                break;

            default:
                break;
        }
    }
    else {
        this->wildCardFace = to_string(tempFace);
    }
}
