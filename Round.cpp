/*
 ************************************************************
 * Name: Bibhash Mulmi                                      *
 * Project: P1 Five Crowns CPP                              *
 * Class: OPL Fall 19                                       *
 * Date: 10/23/2019                                         *
 ************************************************************
*/

// Created by bibhash on 9/12/19.


#include <iomanip>
#include "Round.hpp"

Round::Round(int roundNumber, Player* player[]) {
    this->roundNumber = roundNumber;
    this->player = player;
    this->totalNumPlayers = 2;
    this->saveAndQuit = false;
}

/**********************************************************************
 * Function Name: play
 * Purpose: To shuffle deck, distribute cards and start the fresh round
 * Parameters:
 *          None
 * Return Value: None
 * Local Variables:
 *          None
 * Algorithm:
 *          1) Set wild card
 *          2) Shuffle the deck
 *          3) Distribute Cards
 *          4) Discard a Card
 *          5) Start the round
 * Assistance Received: None
 **********************************************************************/
// this starts a new fresh round
void Round::play() {
    deck = &(Deck::getInstanceOfDeck(2));

    deck->setWildCard(roundNumber + 2);

    deck->shuffleDeck();

    distributeCards();

    deck->discard(deck->drawCard());

    start();
}

/**********************************************************************
 * Function Name: start
 * Purpose: To assign next player and play the round
 * Parameters:
 *          None
 * Return Value: None
 * Local Variables:
 *          prev, a string value. It holds the current player's Assembled
 *          hand as string before making a move.
 *
 *          scr, an int value. It holds the current player's hand score
 *          before making a move.
 * Algorithm:
 *               1) Set the next player by checking who went out in the
 *                  last round
 *               2) Set both player's goOut flags to false.
 *               3) While the round does not end, let the players play.
 *                  Change players after each player makes a move.
 *               4) Check if player saved or quit the game. Set the
 *                  saveGame or quitGame flags and return from this
 *                  function.
 *               5) After the round ends, call endRound function to
 *                  display end scores.
 * Assistance Received: None
 **********************************************************************/
void Round::start() {
    // set the player who went out first from last round as the next player
    nextPlayer = player[1]->hasGoneOut() ? 1 : 0;
    currPlayer = nextPlayer;

    // now set the goOut for both players to false
    player[1]->setGoneOut(false);
    player[0]->setGoneOut(false);

    while (!roundEnded()) {
        printRoundStatus();

        string prev = player[nextPlayer]->getAssembledHandAsString();
        int scr = player[nextPlayer]-> getHandScore();

        player[nextPlayer]->play();

        cout << "Previous Hand: " << prev
            << "Score: " << scr << endl;
        cout << "Current Hand: " << player[nextPlayer]->getAssembledHandAsString()
            << "Score: " << player[nextPlayer]-> getHandScore() << "\n" << endl;

        if (player[nextPlayer]->hasQuitGame()) {
            cout << "===== Quitting the game =====" << endl;
            exit (1);
        }

        if (player[nextPlayer]->hasSaveGame()) {
            setSaveGame(true);
            player[nextPlayer]->setSaveGame(false);
            return;
        }
        else {
            currPlayer = nextPlayer;
            nextPlayer = (nextPlayer + 1) % totalNumPlayers;
        }
    }

    cout << "\n===== Round " << roundNumber << " is Ending. Last Turn! =====\n" << endl;
    endRound();

}

/**********************************************************************
 * Function Name: load
 * Purpose: To load the round
 * Parameters:
 *          info, a vector of String. It holds the round information.
 * Return Value: None
 * Local Variables:
 *          rawInfo, a vector of String. It holds the copy of info.
 *
 *          computerHand, a vector of Cards. It holds the cards for
 *          computer
 *
 *          humanHand, a vector of Cards that holds the cards for human.
 *
 *          drawPile, a deque of Cards that holds the draw pile loaded
 *          from info.
 *
 *          discardPile, a deque of Cards that holds the discard pile
 *          loaded from info
 *
 *          firstPlayer, a string value. It holds the next player's type.
 * Assistance Received: None
 **********************************************************************/
void Round::load(vector<string> info) {
    deck = &(Deck::getInstanceOfDeck(2));
    deck->setWildCard(roundNumber + 2);

    vector <string> rawInfo = info;

    int computerScore = stoi(rawInfo[1]);
    int humanScore = stoi(rawInfo[4]);
    vector<Cards> computerHand = loadHands(rawInfo[2]);
    vector<Cards> humanHand = loadHands(rawInfo[5]);
    deque<Cards> drawPile = loadDeck(rawInfo[6]);
    deque<Cards> discardPile = loadDeck(rawInfo[7]);


    string firstPlayer = player[0]->getType();
    if (Utils::toLowerCase(firstPlayer) == "computer") {
        player[0]->setScore(computerScore);
        player[0]->setHand(computerHand);
        player[1]->setScore(humanScore);
        player[1]->setHand(humanHand);
    }
    else {
        player[1]->setScore(computerScore);
        player[1]->setHand(computerHand);
        player[0]->setScore(humanScore);
        player[0]->setHand(humanHand);
    }

    deck->setDrawPile(drawPile);
    deck->setDiscardPile(discardPile);
}

/**********************************************************************
 * Function Name: loadHands
 * Purpose: To load a vector of Cards from a string of Cards
 * Parameters:
 *          cards, a string value that holds the cards to be loaded.
 * Return Value: A hand with Cards objects.
 * Local Variables:
 *          ss, an istringstream object for reading individual cards
 *          from the string separated by space.
 *
 *          card, a string value that stores the card read from string.
 *
 *          temp, a vector or Cards object that holds the Card objects
 *          created after reading them from string.
 *
 *          face, a string value. It holds the face of Card.
 *
 *          suite, a string value. It holds the suite of Card.
 * Algorithm:
 *               1) Read each card from string separated by space.
 *               2) Store the face and suite using substr function.
 *               3) Add the created Cards object into the temp vector.
 *               4) Return the temp vector.
 * Assistance Received: None
 **********************************************************************/
vector<Cards> Round::loadHands(string cards) {
    istringstream ss(cards);
    string card;
    vector<Cards> temp;

    while(getline(ss, card, ' ')) {
        string face = card.substr(0,card.length()-1);
        string suite = card.substr(card.length()-1);
        temp.emplace_back(Cards(face, suite));
    }

    return temp;
}

/**********************************************************************
 * Function Name: loadDeck
 * Purpose: To load a deque of Cards from a string of Cards
 * Parameters:
 *          cards, a string value that holds the cards to be loaded.
 * Return Value: A pile with Cards objects.
 * Local Variables:
 *          ss, an istringstream object for reading individual cards
 *          from the string separated by space.
 *
 *          card, a string value that stores the card read from string.
 *
 *          temp, a vector or Cards object that holds the Card objects
 *          created after reading them from string.
 *
 *          face, a string value. It holds the face of Card.
 *
 *          suite, a string value. It holds the suite of Card.
 * Algorithm:
 *               1) Read each card from string separated by space.
 *               2) Store the face and suite using substr function.
 *               3) Add the created Cards object into the temp deque.
 *               4) Return the temp vector.
 * Assistance Received: None
 **********************************************************************/
deque<Cards> Round::loadDeck(string cards) {
    istringstream ss(cards);
    string card;
    deque<Cards> temp;

    while(getline(ss, card, ' ')) {
        string face = card.substr(0,card.length()-1);
        string suite = card.substr(card.length()-1);
        temp.emplace_back(Cards(face, suite));
    }

    return temp;
}

/**********************************************************************
 * Function Name: distributeCards
 * Purpose: To assign cards to hands of both players
 * Parameters:
 *          None
 * Return Value: None
 * Local Variables:
 *          hand, a vector of Cards object that stores the cards for player's
 *          hand.
 * Algorithm:
 *               1) For every player, create a vector of cards, add cards from
 *                  draw pile to it, and set the player's hand as that vector of
 *                  cards.
 * Assistance Received: None
 **********************************************************************/
// sets hands of the players
void Round::distributeCards() {
    for (int i = 0; i < totalNumPlayers; i++) {
        vector<Cards> hand;
        for (int j = 0; j < roundNumber + 2; j++) {
            hand.push_back(deck->drawCard());
        }
        player[i]->setHand(hand);
    }
}

/**********************************************************************
 * Function Name: printRoundStatus
 * Purpose: To print the round status
 * Parameters:
 *          None
 * Return Value: None
 * Local Variables:
 *          None
 * Assistance Received: None
 **********************************************************************/
void Round::printRoundStatus() {
    cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << endl;
    cout << left << setw(10) << "Round Number: " << roundNumber << endl;
    cout << "\n";
    for (int i = 0; i < totalNumPlayers; i++) {
        cout << setw(10) << player[i]->getType() << "\n";
        cout << setw(10) << "Score " << player[i]->getScore() << endl;
        cout << setw(10) << "Hand " << player[i]->getHandAsString() << endl;
        cout << "\n";
    }
    cout << setw(10) << "Draw Pile: ";
    cout << deck->getDrawPile();
    cout << endl;
    cout << setw(10) << "Discard Pile: " << deck->showDiscardCard().toString() << endl;
    cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << endl;
}

/**********************************************************************
 * Function Name: roundEnded
 * Purpose: To check if the player has gone out or not
 * Parameters:
 *          None
 * Return Value: Boolean
 * Local Variables:
 *          None
 * Assistance Received: None
 **********************************************************************/
//checks to see if the previous player can go out or not.
bool Round::roundEnded() {
    return player[currPlayer]->hasGoneOut();
}

/**********************************************************************
 * Function Name: getSerializableInfo
 * Purpose: To generate a single string of serialized info of the current
 *          status of round
 * Parameters:
 *          None
 * Return Value: A string value that will be written to a txt file.
 * Local Variables:
 *          humanScore, a string value that holds the human player's score.
 *
 *          humanHand, a string value that holds the human player's hand cards.
 *
 *          computerScore, a string value that holds the computer player's score.
 *
 *          computerHand, a string value that holds the computer player's hand cards.
 *
 *          serializedText, a string value that holds the round status.
 * Assistance Received: None
 **********************************************************************/
const string Round::getSerializableInfo() {
    string serializedText;
    string humanScore, humanHand, computerScore, computerHand;

    for (int i = 0; i < totalNumPlayers; i++) {
        string type = player[i]->getType();
        type = Utils::trim(type);

        if (Utils::toLowerCase(type) == "human") {
            humanHand = player[i]->getHandAsString();
            int scr = player[i]->getScore();
            humanScore = to_string(scr);
        }
        if (Utils::toLowerCase(type) == "computer") {
            computerHand = player[i]->getHandAsString();
            int scr = player[i]->getScore();
            computerScore = to_string(scr);

        }
    }
    serializedText += "Round: " + to_string(roundNumber) + "\n";
    serializedText += "\nComputer:\n";
    serializedText +=   "\tScore: " + computerScore + "\n" +
                        "\tHand: " + computerHand + "\n";
    serializedText += "\nHuman:\n";
    serializedText +=   "\tScore: " + humanScore + "\n" +
                        "\tHand: " + humanHand + "\n";
    serializedText += "\nDraw Pile: " + deck->getDrawPile() + "\n";
    serializedText += "\nDiscard Pile: " + deck->getDiscardPile() + "\n";
    serializedText += "\nNext Player: " + player[nextPlayer]->getType() + "\n";

    return serializedText;
}

/**********************************************************************
 * Function Name: endRound
 * Purpose: To let next player play their last turn and print end of round
 *          status
 * Parameters:
 *          None
 * Return Value: None
 * Local Variables:
 *          earned, an int value that holds the losing player's score.
 * Algorithm:
 *          1) Let next player play their turn.
 *          2) Check if they have saved or quit the game.
 *          3) Print end of round information.
 * Assistance Received: None
 **********************************************************************/
void Round::endRound() {
    // next player plays a turn
    printRoundStatus();
    player[nextPlayer]->play();

    // set the goOut of this player to false because it should not matter at this point
    player[nextPlayer]->setGoneOut(false);

    if (player[nextPlayer]->hasSaveGame()) {
        cout << "You cannot save the game now. " << endl;
        player[nextPlayer]->setSaveGame(false);
        endRound();
    }
    if (player[nextPlayer]->hasQuitGame()) {
        cout << "==== Quitting the game ====" << endl;
        exit (1);
    }

    // now end the round
    cout << "*************************************************************************\n";
    cout << "* " << player[currPlayer]->getType() << ":\n";
    cout << "* Hand: " << player[currPlayer]->getAssembledHandAsString();
    cout << "Score Earned: 0\n";
    player[currPlayer]->updateScore(0);

    cout << "* " << player[nextPlayer]->getType() << ":\n";
    cout << "* Hand: " << player[nextPlayer]->getAssembledHandAsString();
    int earned = player[nextPlayer]->getHandScore();
    cout << "Score Earned: " << earned << endl;
    player[nextPlayer]->updateScore(earned);
    cout << "*************************************************************************\n";

    cout << "\n" << endl;
}