/*
 ************************************************************
 * Name: Bibhash Mulmi                                      *
 * Project: P1 Five Crowns CPP                              *
 * Class: OPL Fall 19                                       *
 * Date: 10/23/2019                                         *
 ************************************************************
*/

// Created by bibhash on 10/16/19.

#ifndef FIVE_CROWNS_CPP_ASSEMBLED_HPP
#define FIVE_CROWNS_CPP_ASSEMBLED_HPP


#include "Cards.hpp"
#include <vector>

class Assembled {
public:
    Assembled() = default;
    explicit Assembled (vector<Cards> hand) {
        parentHand = hand;
        bestCombo = {};
        bestChild = NULL;
    };
    ~Assembled() = default;
    Assembled& operator = (Assembled const&) = default;

    vector<Cards> parentHand;
    vector<Cards> bestCombo;
    Assembled* bestChild;

    /**********************************************************************
    * Function Name: size
    * Purpose: To calculate the number of combinations in the Assembled Hand
    * Parameters:
    *              None
    * Return Value: The size of the total combinations in Hand
    * Local Variables:
    *              size, an integer to store the size
    * Algorithm:
    *               1) increase the size by 1 until the bestChild is NULL
    * Assistance Received: None
    **********************************************************************/
    int size() const {
        int size = 0;
        const Assembled *temp = this;
        while (temp->bestChild != NULL) {
            size++;
            temp = temp->bestChild;
        }
        return size;
    }

};


#endif //FIVE_CROWNS_CPP_ASSEMBLED_HPP
