//
// Created by bibhash on 9/12/19.
//

#include <iomanip>
#include "Round.hpp"

Round::Round(int roundNumber, Player* player[]) {
    this->roundNumber = roundNumber;
    this->player = player;
    this->totalNumPlayers = 2;
    this->saveAndQuit = false;
}

// this starts a new fresh round
void Round::play() {
    deck = &(Deck::getInstanceOfDeck(2));

    // set the wild card
    deck->setWildCard(roundNumber + 2);

    // shuffle cards
    deck->shuffleDeck();

    // set players hands
    distributeCards();

    // set the discard pile
    deck->discard(deck->drawCard());

    start();
}

void Round::start() {
    // set the player who went out first from last round as the next player
    nextPlayer = player[1]->hasGoneOut() ? 1 : 0;
    currPlayer = nextPlayer;

    // set the goOut for both players to false
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
            // change the save game flag of the player
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

// loads Hands of players from serialized string
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

// loads Deck of cards from serialized string
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

//checks to see if the previous player can go out or not.
bool Round::roundEnded() {
    return player[currPlayer]->hasGoneOut();
}

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