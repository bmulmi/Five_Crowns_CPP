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
 * Function Name: Deck
 * Purpose: To construct the Deck object
 * Parameters:
 *              numDecks, an integer passed by value. It holds the number
 *              of decks to build
 * Return Value: None
 * Local Variables:
 *              initialDeck, a deque structure that holds the deque of
 *              the newly created deck of cards
 * Assistance Received: None
 **********************************************************************/
Deck::Deck(int numDecks) {
    // create an initial deck of size numDecks
    deque<Cards> initialDeck = arrangeDeck(numDecks);
    drawPile = initialDeck;
}

/**********************************************************************
 * Function Name: getInstanceOfDeck
 * Purpose: To get the instance of the pointer to the singleton deck class
 *          object
 * Parameters:
 *          num, an integer passed by value. It holds the number of decks
 *          of the object
 * Return Value: pointer to the deck object
 * Local Variables:
 *          None
 * Algorithm:
 *          1) if Deck is not assigned yet, then create new deck object
 *          2) else return the previously assigned deck.
 * Assistance Received: None
 **********************************************************************/
Deck& Deck::getInstanceOfDeck(int num) {
    if (deck == nullptr){
        deck = new Deck(num);
    }
    return *deck;
}


/**********************************************************************
 * Function Name: createDeck
 * Purpose: To create a singe deck of cards
 * Parameters:
 *              None
 * Return Value: The single deck of cards, a deque of Cards object
 * Local Variables:
 *              temp, a deque of Cards object. It holds the newly created
 *              Cards object.
 * Algorithm:
 *               1) For each suite and face create the Cards object and
 *               push it into the returning vector
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
 * Function Name: arrangeDeck
 * Purpose: To create and combine the number of decks
 * Parameters:
 *              numDecks, an integer value. It holds the number of decks
 *              to create and combine for the game.
 * Return Value: the created and combined complete deck.
 * Local Variables:
 *              initialDeck, a deque of Cards object. It holds the entire
 *              deck of Cards.
 *              
 * Algorithm:
 *               1) Create new deque of Cards and combine it to the initialDeck
 *               by pushing each card of the newly created deck into it.
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
 * Function Name: createJokers
 * Purpose: To create the number of jokers in the deck
 * Parameters:
 *              num, an integer value. It holds the number of Joker cards
 *              to create for the deck.
 * Return Value: the deque of Cards object
 * Local Variables:
 *              temp, a deque of Cards. It holds the deque of Joker Cards
 * Algorithm:
 *               1) Create the number of Joker Cards and push it into the
 *               temp deque
 * Assistance Received: None
 **********************************************************************/
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
 * Function Name: shuffleDeck
 * Purpose: To clear the card piles and create new deck and shuffle the cards
 * Parameters:
 *              None
 * Return Value: None
 * Local Variables:
 *              None
 * Algorithm:
 *               1) Clear discard and draw pile
 *               2) Assign cards to draw pile
 *               3) shuffle the Draw pile
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
 * Function Name: drawCard
 * Purpose: To draw the top card of the draw pile
 * Parameters:
 *              None
 * Return Value: The top card of the draw pile
 * Local Variables:
 *              temp, a Cards object. It holds the top card of the draw pile
 * Assistance Received: None
 **********************************************************************/
// returns top card of the draw pile and pops it from the pile
Cards Deck::drawCard() {
    Cards temp = drawPile.front();
    drawPile.pop_front();
    return temp;
}

/**********************************************************************
 * Function Name: discard
 * Purpose: to put the Card into discard pile
 * Parameters:
 *              a_card, a Cards object. It holds the card to be discarded
 * Return Value: None
 * Local Variables: None
 * Assistance Received: None
 **********************************************************************/
void Deck::discard(Cards a_card) {
    this->discardPile.push_front(a_card);
}

/**********************************************************************
 * Function Name: showDiscardCard
 * Purpose: To get the top card of the discard pile but not remove it
 * Parameters:
 *              None
 * Return Value: The top card of the Discard Pile
 * Local Variables:
 *              None
 * Assistance Received: None
 **********************************************************************/
Cards Deck::showDiscardCard() {
    return discardPile.front();
}

/**********************************************************************
 * Function Name: drawDiscardCard
 * Purpose: To draw the discard pile card
 * Parameters:
 *              None
 * Return Value: The top card of the discard pile
 * Local Variables:
 *              temp, a Cards object. It holds the top card of the discard
 *              pile
 * Assistance Received: None
 **********************************************************************/
// returns top card of the discard pile and pops it from the pile
Cards Deck::drawDiscardCard() {
    Cards temp = discardPile.front();
    discardPile.pop_front();
    return temp;
}

/**********************************************************************
 * Function Name: getDiscardPile
 * Purpose: to get the cards of the discard pile as string
 * Parameters:
 *              None
 * Return Value: String of Discard pile Cards
 * Local Variables:
 *              temp, a string value. It holds the Cards of Discard Pile
 * Algorithm:
 *               1) String concatenate each Card as string into temp
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
 * Function Name: getDrawPile
 * Purpose: To get the cards of the draw pile as string
 * Parameters:
 *              None
 * Return Value: the String of Draw pile Cards
 * Local Variables:
 *              temp, a string value. It holds the string representation of
 *              draw pile cards
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
 * Function Name: setDiscardPile
 * Purpose: To clear the old discard pile and assign a new one
 * Parameters:
 *              cards, a deque of Cards object.
 * Return Value: None
 * Local Variables:
 *              None
 * Assistance Received: None
 **********************************************************************/
void Deck::setDiscardPile(deque<Cards> cards) {
    discardPile.clear();
    discardPile = cards;
}

/**********************************************************************
 * Function Name: setDrawPile
 * Purpose: To clear the old draw pile and assign a new one
 * Parameters:
 *          cards, a deque of Cards object.
 * Return Value: None
 * Local Variables:
 *          None
 * Assistance Received: None
 **********************************************************************/
void Deck::setDrawPile(deque<Cards> cards) {
    drawPile.clear();
    drawPile = cards;
}

/**********************************************************************
 * Function Name: setWildCard
 * Purpose: to set the wildCard face
 * Parameters:
 *          faceValue, an int value. It holds the faceValue of the wildCard.
 * Return Value: None
 * Local Variables:
 *          tempFace, an int value. It copies the faceValue passed in as
 *          parameter.
 * Algorithm:
 *               1) if the tempFace is greater than 9, convert it to the
 *               respective face
 *               2) else convert the int to string
 *               3) assign the wildCardFace of this Deck object.
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
