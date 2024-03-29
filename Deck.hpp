/*
 ************************************************************
 * Name: Bibhash Mulmi                                      *
 * Project: P1 Five Crowns CPP                              *
 * Class: OPL Fall 19                                       *
 * Date: 10/23/2019                                         *
 ************************************************************
*/

// Created by bibhash on 9/10/19.


#include "Cards.hpp"
#include <vector>
#include <queue>
#include <iostream>
#include <chrono>

#ifndef FIVE_CROWNS_CPP_DECK_HPP
#define FIVE_CROWNS_CPP_DECK_HPP

using namespace std;

class Deck {
public:
    Deck& operator = (Deck const&) = delete;
    ~Deck() = default;

    //-----selectors-----
    static Deck& getInstanceOfDeck(int num);
    string getWildCardFace () { return this->wildCardFace; }
    string getDiscardPile();
    string getDrawPile();
    Cards showDiscardCard();

    //-----mutators-----
    void setDrawPile(deque<Cards> cards);
    void setDiscardPile(deque<Cards> cards);
    void setWildCard(int faceValue);
    Cards drawDiscardCard();
    Cards drawCard();
    void discard(Cards a_card);

    //-----utility functions-----
    void shuffleDeck();

private:
    Deck() = default;
    explicit Deck(int numDecks);

    static Deck *deck;

    static deque<Cards> drawPile;
    static deque<Cards> discardPile;

    string wildCardFace;
    int const numberOfJokers = 3;
    string const suite [5] = {"S", "C", "D", "H", "T"};
    string const face [11] = {"3", "4", "5", "6", "7", "8",
                              "9", "X", "J", "Q", "K"};

    //-----utility functions-----
    deque<Cards> createJokers(int num);
    deque<Cards> createDeck();
    deque<Cards> arrangeDeck(int numDecks);
};



#endif //FIVE_CROWNS_CPP_DECK_H
