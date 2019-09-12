//
// Created by bibhash on 9/10/19.
//

#include "Cards.hpp"
#include <vector>
#include <queue>
#include <iostream>

#ifndef FIVE_CROWNS_CPP_DECK_H
#define FIVE_CROWNS_CPP_DECK_HPP

using namespace std;

class Deck {
public:
    Deck();
    Deck(int numDecks);
    ~Deck();
    void printDeck();
    void shuffleDeck();
    vector<Cards> getCards(int numCards);

private:
    deque<Cards> deck;
    deque<Cards> discardPile;
    deque<Cards> drawPile;

    deque<Cards> createJokers(int num);
    deque<Cards> createDeck();

    int const numberOfJokers = 3;
    string const suite [5] = {"S", "C", "D", "H", "T"};
    string const face [11] = {"3", "4", "5", "6", "7", "8",
                              "9", "10", "J", "Q", "K"};
};


#endif //FIVE_CROWNS_CPP_DECK_H
