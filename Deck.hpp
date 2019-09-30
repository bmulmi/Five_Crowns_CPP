//
// Created by bibhash on 9/10/19.
//

#include "Cards.hpp"
#include <vector>
#include <queue>
#include <iostream>
#include <time.h>

#ifndef FIVE_CROWNS_CPP_DECK_HPP
#define FIVE_CROWNS_CPP_DECK_HPP

using namespace std;

class Deck {
public:
    Deck& operator = (Deck const&) = delete;
    ~Deck() = default;
    static Deck& getInstanceOfDeck(int num);

    void printDeck();
    void shuffleDeck();
    void discard(Cards a_card);
    void showDrawPile();
    void setDrawPile(deque<Cards> cards);
    void setDiscardPile(deque<Cards> cards);
    void setWildCard(int faceValue);
    string getWildCardFace () { return this->wildCardFace; }
    string getDiscardPile();
    string getDrawPile();

    Cards showDiscardCard();
    Cards drawDiscardCard();
    Cards drawCard();

private:
    Deck(int numDecks);
    static Deck *deck;

    static deque<Cards> drawPile;
    static deque<Cards> discardPile;

    deque<Cards> createJokers(int num);
    deque<Cards> createDeck();
    deque<Cards> arrangeDeck(int numDecks);

    string wildCardFace;
    int const numberOfJokers = 3;
    string const suite [5] = {"S", "C", "D", "H", "T"};
    string const face [11] = {"3", "4", "5", "6", "7", "8",
                              "9", "10", "J", "Q", "K"};
};


#endif //FIVE_CROWNS_CPP_DECK_H
