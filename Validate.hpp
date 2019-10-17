//
// Created by bibhash on 9/29/19.
//

#ifndef FIVE_CROWNS_CPP_VALIDATE_HPP
#define FIVE_CROWNS_CPP_VALIDATE_HPP


#include "Cards.hpp"
#include <vector>
#include <climits>

namespace Validate {
    int calculateScore(vector<Cards> a_hand);
    bool isRun(vector<Cards> a_hand);
    bool isBook (vector<Cards> a_hand);
    bool hasSameSuite(vector<Cards> a_hand);
    bool canBeRun(vector<Cards> a_cards, int &missingCardsCount);
    void sortCards(vector<Cards> &a_hand);
    void swapCards(Cards *left, Cards *right);
    vector<Cards> extractJokerCards(vector<Cards> &hand);
    vector<Cards> extractWildCards(vector<Cards> &a_hand);
}


#endif //FIVE_CROWNS_CPP_VALIDATE_HPP
