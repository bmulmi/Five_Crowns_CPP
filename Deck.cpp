//
// Created by bibhash on 9/10/19.
//

#include "Deck.hpp"
#include <bits/stdc++.h>
using namespace std;

Deck* Deck::deck = NULL;
deque<Cards> Deck::drawPile;
deque<Cards> Deck::discardPile;

Deck::Deck(int numDecks) {
    // create an initial deck
    deque<Cards> initialDeck = arrangeDeck(numDecks);
    drawPile = initialDeck;
}

Deck& Deck::getInstanceOfDeck(int num) {
    if (deck == nullptr){
        deck = new Deck(num);
    }
    return *deck;
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

// arranges the number of decks into one deck
deque<Cards> Deck::arrangeDeck(int numDecks) {
    deque<Cards> initialDeck;

    for (int i = 0; i < numDecks; i++) {
        deque<Cards> secondaryDeck = createDeck();
        // push each card into the initial deck
        for (auto a_card : secondaryDeck) {
            initialDeck.push_back(a_card);
        }
    }

    return initialDeck;
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

// mixes the discard pile into draw pile and shuffles the deck
void Deck::shuffleDeck() {
    unsigned seed = time(NULL);

    // clear both the piles
    drawPile.clear();
    discardPile.clear();

    // arrange the draw pile
    drawPile = arrangeDeck(2);

    // shuffle the draw pile
    shuffle(drawPile.begin(), drawPile.end(), default_random_engine(seed));
}

// returns top card of the draw pile and pops it from the pile
Cards Deck::drawCard() {
    Cards temp = drawPile.front();
    drawPile.pop_front();
    return temp;
}

// pushes card into top of discard pile
void Deck::discard(Cards a_card) {
    this->discardPile.push_front(a_card);
}

// returns top card of the discard pile
Cards Deck::showDiscardCard() {
//    cout << "Discard Card returning: " << this->discardPile.front().toString();
    return discardPile.front();
}

// returns top card of the discard pile and pops it from the pile
Cards Deck::drawDiscardCard() {
    Cards temp = discardPile.front();
    discardPile.pop_front();
    return temp;
}

string Deck::getDiscardPile() {
    string temp;

    for (auto each : this->discardPile) {
        temp += each.toString() + " ";
    }

    return temp;
}

string Deck::getDrawPile() {
    string temp;

    for (auto each : this->drawPile) {
        temp += each.toString() + " ";
    }

    return temp;
}

void Deck::setDiscardPile(deque<Cards> cards) {
    this->discardPile.clear();
    this->discardPile = cards;
}

void Deck::setDrawPile(deque<Cards> cards) {
    this->drawPile.clear();
    this->drawPile = cards;
}

void Deck::setWildCard(int faceValue) {
    int tempFace = faceValue;

    if (tempFace > 10) {
        switch (tempFace) {
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
