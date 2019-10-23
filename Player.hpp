/*
 ************************************************************
 * Name: Bibhash Mulmi                                      *
 * Project: P1 Five Crowns CPP                              *
 * Class: OPL Fall 19                                       *
 * Date: 10/23/2019                                         *
 ************************************************************
*/

// Created by bibhash on 9/11/19.


#ifndef FIVE_CROWNS_CPP_PLAYER_HPP
#define FIVE_CROWNS_CPP_PLAYER_HPP


#include <vector>
#include <iostream>
#include <algorithm>
#include <string.h>

#include "Cards.hpp"
#include "Deck.hpp"
#include "Validate.hpp"
#include "Utilities.hpp"
#include "Assembled.hpp"

using namespace std;
using namespace Validate;

class Player {
public:
    Player();
    ~Player() = default;

    // -----selectors-----
    int getHandScore();
    int getCardIndex(vector<Cards> a_hand, Cards a_card) const;
    string getAssembledHandAsString();
    string getHandAsString();
    bool canGoOut(vector<Cards> a_hand);
    virtual string getType() const = 0;

    /**********************************************************************
     * Function Name: getScore
     * Purpose: To get score of the player
     * Parameters: None
     * Return Value: Score of player
     * Local Variables: None
     * Assistance Received: None
     **********************************************************************/
    int getScore() const { return score; }

    /**********************************************************************
     * Function Name: hasQuitGame
     * Purpose: To get quitGame flag of player
     * Parameters: None
     * Return Value: Boolean value. True if player chose to quit game, false otherwise
     * Local Variables: None
     * Assistance Received: None
     **********************************************************************/
    bool hasQuitGame() { return quitGame; }

    /**********************************************************************
     * Function Name: hasSaveGame
     * Purpose: To check if player has chose to save game
     * Parameters: None
     * Return Value: Boolean value. True if player chose to save game, false otherwise.
     * Local Variables: None
     * Assistance Received: None
     **********************************************************************/
    bool hasSaveGame() { return saveGame; }

    /**********************************************************************
     * Function Name: hasGoneOut
     * Purpose: To check if player has gone out
     * Parameters: None
     * Return Value: Boolean value. True if player went out, false otherwise.
     * Local Variables: None
     * Assistance Received: None
     **********************************************************************/
    bool hasGoneOut() { return goneOut; }

    //-----mutators-----
    /**********************************************************************
     * Function Name: setScore
     * Purpose: To set score of player
     * Parameters: a_score, an int value that holds the score of player
     * Return Value: None
     * Local Variables: None
     * Assistance Received: None
     **********************************************************************/
    inline void setScore( int a_score ) { this->score = a_score; }

    /**********************************************************************
     * Function Name: setHand
     * Purpose: To assign hand to player
     * Parameters: a_hand, a vector of Cards object that holds the hand of player.
     * Return Value: None
     * Local Variables: None
     * Assistance Received: None
     **********************************************************************/
    inline void setHand (vector<Cards> a_hand) { this->hand = a_hand; }

    /**********************************************************************
     * Function Name: setQuitGame
     * Purpose: To set quitGame flag for player
     * Parameters: val, a boolean value.
     * Return Value: None
     * Local Variables: None
     * Assistance Received: None
     **********************************************************************/
    inline void setQuitGame(bool val) { quitGame = val; }

    /**********************************************************************
     * Function Name: setSaveGame
     * Purpose: To set saveGame flag for the player
     * Parameters: val, a boolean value.
     * Return Value: None
     * Local Variables: None
     * Assistance Received: None
     **********************************************************************/
    inline void setSaveGame(bool val) { saveGame = val; }

    /**********************************************************************
     * Function Name: setGoneOut
     * Purpose: To set goneOut flag for player
     * Parameters: val, a boolean value.
     * Return Value: None
     * Local Variables: None
     * Assistance Received: None
     **********************************************************************/
    inline void setGoneOut(bool val) { goneOut  = val;}

    /**********************************************************************
     * Function Name: updateScore
     * Purpose: To add score to current score of player
     * Parameters: a_score, an int value that holds the score to be added.
     * Return Value: None
     * Local Variables: None
     * Assistance Received: None
     **********************************************************************/
    inline void updateScore(int a_score) { this->score += a_score; }

    /**********************************************************************
     * Function Name: removeFromHand
     * Purpose: To remove a card from player's hand
     * Parameters: discardIndex, an int value that holds the index of card to
     *              be removed
     * Return Value: None
     * Local Variables: None
     * Assistance Received: None
     **********************************************************************/
    inline void removeFromHand(int discardIndex) { hand.erase(hand.begin() + discardIndex); }
    virtual void setType(string type) = 0;

    virtual void goOut() = 0;
    virtual void play() = 0;
    virtual void pickCard() = 0;

protected:
    int score;
    string type;
    bool goneOut;
    bool saveGame;
    bool quitGame;
    Deck* deck;
    vector<Cards> hand;

    //-----help mode functions-----
    string whichPileToChoose();
    int whichCardToDiscard();
    vector<vector<Cards>> assemblePossibleHand();

private:
    //-----strategy functions-----
    vector<vector<Cards>> getBooksAndRuns(vector<Cards> a_hand);
    vector<vector<Cards>> getSameSuiteHands(vector<Cards> a_hand);
    int getLowestScore (vector <Cards> &a_hand, Assembled *assembled_hands);
    void getBooksOrRuns(vector<Cards> a_hand, vector<vector<Cards>> &a_collection, int check_type);
    void combineAndCheck (vector<Cards> a_hand, vector<Cards> a_cards, vector<vector<Cards>> &collection, int check_type);
    void combineTwoAndCheck (vector<Cards> a_hand, vector<Cards> a_cards1, vector<Cards> a_cards2, vector<vector<Cards>> &collection, int check_type);
    void removeCards (vector<Cards> &a_hand, vector<Cards> cards);
};


#endif //FIVE_CROWNS_CPP_PLAYER_HPP
