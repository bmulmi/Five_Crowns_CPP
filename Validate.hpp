//
// Created by bibhash on 9/29/19.
//

#ifndef FIVE_CROWNS_CPP_VALIDATE_HPP
#define FIVE_CROWNS_CPP_VALIDATE_HPP


#include "Cards.hpp"
#include <vector>
#include <climits>

namespace Validate {
    int calculateScoreOfHand (vector<Cards> a_hand);
    int calculateRealScore (vector<Cards> a_hand);
    bool isRun(vector<Cards> a_hand);
    bool isBook (vector<Cards> a_hand);
    bool hasSameSuite(vector<Cards> a_hand);
    bool compareIntervalCards(Cards left, Cards right);
    bool canBeRun(vector<Cards> a_cards, int &missingCardsCount);
    int checkCombo(vector<Cards> permutedHands, vector<int> combos);
    void sortCards(vector<Cards> &a_hand);
    void swapCards(Cards *left, Cards *right);
    void permute(vector<Cards> a_hand, int left, int right, vector<vector<Cards>>& permuted);

    vector<Cards> extractJokerCards(vector<Cards> &hand);
    vector<Cards> extractWildCards(vector<Cards> &a_hand);
    vector<Cards> extractWildCardsSameSuite(vector<Cards> &a_hand, string a_suite);
    vector<Cards> extractWildCardsDiffSuite(vector<Cards> &a_hand, string a_suite);

    vector<vector<int>> getCombinationIndices(int size);


};


#endif //FIVE_CROWNS_CPP_VALIDATE_HPP
