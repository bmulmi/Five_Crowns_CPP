//
// Created by bibhash on 10/16/19.
//

#ifndef FIVE_CROWNS_CPP_ASSEMBLED_HPP
#define FIVE_CROWNS_CPP_ASSEMBLED_HPP


#include "Cards.hpp"
#include <vector>

class Assembled {
public:
    vector<Cards> parentHand;
    vector<Cards> bestCombo;
    Assembled* bestChild;

    Assembled (vector<Cards> hand) {
        parentHand = hand;
        bestCombo = {};
        bestChild = NULL;
    }

    int size() {
        int size = 0;
        Assembled *temp = this;
        while (temp->bestChild != NULL) {
            size++;
            temp = temp->bestChild;
        }
        return size;
    }

};


#endif //FIVE_CROWNS_CPP_ASSEMBLED_HPP
