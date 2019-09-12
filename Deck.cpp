//
// Created by bibhash on 9/10/19.
//

#include "Deck.hpp"
#include <bits/stdc++.h>
using namespace std;

//creates a single deck of cards
Deck::Deck() {
    this->deck = createDeck();


}

Deck::Deck(int numDecks) {
    // create an initial deck
    deque<Cards> initialDeck = createDeck();

    for (int i = 1; i < numDecks; i++) {
        deque<Cards> secondaryDeck = createDeck();
        for (auto a_card : secondaryDeck) {
            initialDeck.push_back(a_card);
        }
    }

    this->deck = initialDeck;
}

Deck::~Deck() {

}

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

void Deck::printDeck() {
    cout << "# Cards: " << this->deck.size() << endl;

    for(auto a_card : this->deck) {
        cout << a_card.toString() << " ";
    }
    cout << endl;
}

void Deck::shuffleDeck() {
    unsigned seed = 0;
    shuffle(this->deck.begin(), this->deck.end(), default_random_engine(seed));
}

vector<Cards> Deck::getCards(int numCards) {
    vector<Cards> temp;

    for (int i = 0; i < numCards; i++) {
        temp.push_back(this->deck.front());
        this->deck.pop_front();
    }

    return temp;
}
