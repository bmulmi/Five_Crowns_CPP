/*
 ************************************************************
 * Name: Bibhash Mulmi                                      *
 * Project: P1 Five Crowns CPP                              *
 * Class: OPL Fall 19                                       *
 * Date: 10/23/2019                                         *
 ************************************************************
*/

// Created by bibhash on 9/11/19.


#include "Game.hpp"


/**********************************************************************
 * Function Name: Game
 * Purpose: To construct the Game class object.
 * Parameters:
 *              roundNumber, an int value that holds the round number of
 *              game currently being played.
 * Return Value: None
 * Assistance Received: None
 **********************************************************************/
Game::Game(int roundNumber) {
    this->roundNumber = roundNumber;
}

/**********************************************************************
 * Function Name: start
 * Purpose: To start the game.
 * Parameters:
 *              None
 * Return Value: None
 * Local Variables:
 *              nextPlayer, an int value. Stores the player's turn returned
 *              from Toss function
 * Algorithm:
 *               1) Do the Toss, assign first and second players accordingly.
 *               2) Set scores to 0 for players
 *               3) While round number is less than 12, keep initializing new
 *               Round objects
 *               4) Return from the function if player saves and quits the game.
 *               5) Declare the winner.
 * Assistance Received: None
 **********************************************************************/
void Game::start() {
    int nextPlayer = toss();
    if (nextPlayer == 0) {
        player[0] = new Human();
        player[0]->setType("Human");
        player[1] = new Computer();
        player[1]->setType("Computer");
    }
    else {
        player[0] = new Computer();
        player[0]->setType("Computer");
        player[1] = new Human();
        player[1]->setType("Human");
    }
    cout << "Now, Lets get started!" << endl;

    // set the scores to zero before starting a fresh game
    for (int i = 0; i < 2; i++) {
        player[i]->setScore(0);
    }

    while (roundNumber < 12) {
        Round r(roundNumber, player);
        r.play();

        if (r.isSaveAndQuit()) {
            string roundInfo = r.getSerializableInfo();
            saveGame(roundInfo);
            return;
        }

        roundNumber++;
    }

    declareWinner();
}

/**********************************************************************
 * Function Name: toss
 * Purpose: To toss a coin
 * Parameters:
 *              None
 * Return Value: Int value of 0 if Human wins, 1 if computer wins
 * Local Variables:
 *              side, a char value. It holds the user input for heads or
 *              tails
 *
 *              winner, an int value. It holds the winning random integer
 *              value.
 * Algorithm:
 *               1) Ask user for heads or tails
 *               2) Generate a random number of 0 or 1
 *               3) Return the value.
 * Assistance Received: None
 **********************************************************************/
int Game::toss() {
    char side;
    do {
        cout << ">Time for a toss. Heads or Tails (h/t)? ";
        cin >> side;
    } while (side != 'h' && side != 't');

    srand(time(0));
    int winner = rand() % 2;
    if ((winner == 0 && side == 'h') || (winner == 1 && side == 't')) {
        cout << ">Congratulations! You won the toss." << endl;
        return 0;
    }
    else {
        cout << ">Sorry, you lost the toss." << endl;
        return 1;
    }
}

/**********************************************************************
 * Function Name: load
 * Purpose: To load the game
 * Parameters:
 *              info, a vector of string. It holds the round information to
 *              be loaded.
 * Return Value: None
 * Local Variables:
 *              nextPlayer, a string value. It holds the next player info
 *              from the info vector
 * Algorithm:
 *               1) Get the next player
 *               2) Assign the first player as next player
 *               3) While round number is less than 12 initialize new round
 *               objects. Increase the round Number.
 *               4) If the round is just loaded, then call load function of round
 *               and start the round.
 *               5) If the user wants to save and quit, set the save flag and
 *               return from the function.
 *               6) Declare the winner.
 * Assistance Received: None
 **********************************************************************/
// sets next player and loads the round
void Game::load(vector<string> info) {
    string nextPlayer = Utils::toLowerCase(info[info.size()-1]);
    info.pop_back();

    // set the next player
    cout << ">Next player: " << nextPlayer << endl;

    if (nextPlayer == "human") {
        player[0] = new Human();
        player[0]->setType("Human");
        player[1] = new Computer();
        player[1]->setType("Computer");
    }
    else if (nextPlayer == "computer"){
        player[0] = new Computer();
        player[0]->setType("Computer");
        player[1] = new Human();
        player[1]->setType("Human");
    }
    else {
        cerr << "Invalid Next Player in the serialization file! So, human goes first." << endl;
        player[0] = new Human();
        player[0]->setType("Human");
        player[1] = new Computer();
        player[1]->setType("Computer");
    }

    bool justLoaded = true;

    while (roundNumber < 12) {
        // create the round
        Round r(this->roundNumber, player);

        if (justLoaded){
            r.load(info);
            r.start();
            justLoaded = false;
        }
        else {
            r.play();
        }

        if (r.isSaveAndQuit()) {
            string roundInfo = r.getSerializableInfo();
            saveGame(roundInfo);
            return;
        }

        roundNumber++;
    }
    declareWinner();
}

/**********************************************************************
 * Function Name: saveGame
 * Purpose: To save the game.
 * Parameters:
 *          info, a string value. It holds the string representation of
 *          the round state to be saved.
 * Return Value: None
 * Local Variables:
 *          save, an ofstream object to write the file.
 *
 *          filename, a string value. It holds the filename we want to
 *          use to save.
 * Algorithm:
 *               1) Ask the user for a filename.
 *               2) if the filename cannot be used, re call the function
 *               3) write the info into the file.
 *               4) close the file.
 * Assistance Received: None
 **********************************************************************/
// saves the string of round info into a ofstream object
void Game::saveGame(string info) {
    ofstream save;
    string filename;

    cout << ">Please enter the name of the file you want to save: ";
    cin.ignore();
    cin >> filename;
    filename += ".txt";

    save.open("/home/bibhash/git_repos/Five_Crowns_CPP/savedGames/"+filename);

    if (!save.is_open()) {
        cout << ">Could not use the filename." << endl;
        saveGame(info);
    }

    save << info;
    save.close();
}

/**********************************************************************
 * Function Name: declareWinner
 * Purpose: to declare the winner and print the status
 * Parameters:
 *              None
 * Return Value: None
 * Local Variables:
 *              scr1, an int value. Holds the first player's score.
 *              scr2, an int value. Holds the second player's score.
 *              winner, a string value. Holds the type of winning player.
 *              loser, a string value. Holds the type of losing player.
 *              winnerScr, an int value. Holds the winner score.
 *              loserScr, an int value. Holds the loser score.
 * Algorithm:
 *               1) Get the scores of players and store them.
 *               2) The player with lower score is the winner.
 *               3) Get the winner's score.
 *               4) Print out the end of game info with winner and loser info.
 * Assistance Received: None
 **********************************************************************/
void Game::declareWinner() {
    int scr1 = player[0]->getScore();
    int scr2 = player[1]->getScore();
    string winner = scr1 < scr2 ? player[0]->getType() : player[1]->getType();
    string loser = scr2 < scr1 ? player[0]->getType() : player[1]->getType();
    int winnerScr = scr1 < scr2 ? scr1 : scr2;
    int loserScr = scr2 < scr1 ? scr1 : scr2;

    cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-" << endl;
    cout << winner << " is the Winner!" << endl;
    cout << winner << " total score: " << winnerScr << endl;

    cout << loser << " lost the game... " << endl;
    cout << loser << " total score: " << loserScr << endl;
    cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-" << endl;
}