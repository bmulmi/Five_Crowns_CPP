/*
 ************************************************************
 * Name: Bibhash Mulmi                                      *
 * Project: P1 Five Crowns CPP                              *
 * Class: OPL Fall 19                                       *
 * Date: 10/23/2019                                         *
 ************************************************************
*/

// Created by bibhash on 9/11/19.

#include "FiveCrowns.hpp"


/**********************************************************************
 * Function Name: start
 * Purpose: To start either a new game or load game
 * Parameters:
 *              None
 * Return Value: None
 * Local Variables:
 *              load, a char value. It holds the user input of 'y' or 'n'
 *              when asked whether they want to load a game.
 *
 *              re_start, a char value. It holds the user input of 'y' or 'n'
 *              when asked whether they want to restart the game.
 * Algorithm:
 *               1) Ask the user if they want to load game.
 *               2) Call load game function or start new game function accordingly.
 *               3) Ask the user if they want to restart the game.
 *               4) Call restart game function accordingly.
 * Assistance Received: None
 **********************************************************************/
void FiveCrowns::start() {
    cout << "Welcome to Five Crowns!" << endl;
    char load;
    do {
        cout << ">Do you want to load game? (y/n) ";
        cin >> load;
    } while(load != 'y' && load != 'n');

    if (load == 'y') {
        loadGame();
    }
    else {
        init(1);
        game->start();
    }

    char re_start;
    do {
        cin.ignore();
        cout << ">Do you want to restart the game? (y/n) ";
        cin >> re_start;
    } while (re_start != 'y' && re_start != 'n');

    if (re_start == 'y') {
        restart();
    }

    cout << "===== Thank you for playing Five Crowns! Hope you enjoyed it! =====" << endl;
}

/**********************************************************************
 * Function Name: loadGame
 * Purpose: To load the game from serialized file
 * Parameters:
 *              None
 * Return Value: None
 * Local Variables:
 *              file, a string value. It holds the directory of the file
 *              to be loaded.
 *
 *              filename, a string value. It holds the filename of the user.
 *
 *              save, an ifstream object. It opens the file to be loaded.
 *
 *              roundNumber, an int value. It holds the round number loaded
 *              from file.
 *
 *              roundStats, a vector of string. It hold each line as string from
 *              the loaded file.
 * Algorithm:
 *               1) Get the file name from user. Re-call the function if file
 *               cannot be opened.
 *               2) Get the first line of file and store it into roundNumber.
 *               3) Get each line from the file and save it into the vector.
 *               4) Initialize the Game object.
 *               5) Call load function of Game.
 * Assistance Received: None
 **********************************************************************/
void FiveCrowns::loadGame() {
    string file = "/home/bibhash/git_repos/Five_Crowns_CPP/savedGames/";

    ifstream save;

    string filename;
    cin.ignore();
    cout << ">What is the name of the saved file? ";
    cin >> filename;
    filename.append(".txt");
    file += filename;
    save.open(file);

    if (!save.is_open()) {
        cout << "File Not Found!" << endl;
        loadGame();
    }

    string line;

    // get the round number and store it
    getline(save, line);
    int roundNumber = stoi(Utils::getValue(line));

    // store everything else in a vector of strings
    vector<string> roundStats;
    while(getline(save, line)) {
        if(!line.empty()) {
            string val = Utils::getValue(line);
            roundStats.push_back(Utils::trim(val));
        }
    }

    init(roundNumber);

    game->load(roundStats);
}

FiveCrowns::~FiveCrowns() {
    reset();
}

/**********************************************************************
 * Function Name: restart
 * Purpose: To restart the Game from beginning
 * Parameters:
 *          None
 * Return Value: None
 * Local Variables:
 *          None
 * Assistance Received: None
 **********************************************************************/
void FiveCrowns::restart() {
    reset();
    start();
}

/**********************************************************************
 * Function Name: reset
 * Purpose: To delete the pointer to the game object
 * Parameters:
 *              None
 * Return Value: None
 * Local Variables:
 *              None
 * Assistance Received: None
 **********************************************************************/
void FiveCrowns::reset() {
    delete game;
}

/**********************************************************************
 * Function Name: init
 * Purpose: To assign Game object pointer to the game member variable
 * Parameters:
 *          roundNumber, an int value. It holds the round number of the game.
 * Return Value: None
 * Local Variables:
 *          None
 * Assistance Received: None
 **********************************************************************/
// initializes the round number
void FiveCrowns::init(int roundNumber) {
    game = new Game(roundNumber);
}
