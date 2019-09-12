//
// Created by bibhash on 9/11/19.
//

//#include "FiveCrowns.hpp"
#include "Deck.hpp"

int main(int argc, const char** argv) {
//    FiveCrowns fiveCrowns;
//    fiveCrowns.start();

    Deck deck(2);
    deck.printDeck();
    cout<<endl;
    deck.shuffleDeck();
    deck.printDeck();
    Deck deck2;
    deck2.printDeck();
}
