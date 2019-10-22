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
 * Function Name:
 * Purpose:
 * Parameters:
 *
 * Return Value:
 * Local Variables:
 *
 * Algorithm:
 *               1)
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
 * Function Name:
 * Purpose:
 * Parameters:
 *
 * Return Value:
 * Local Variables:
 *
 * Algorithm:
 *               1)
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
 * Function Name:
 * Purpose:
 * Parameters:
 *
 * Return Value:
 * Local Variables:
 *
 * Algorithm:
 *               1)
 * Assistance Received: None
 **********************************************************************/
void FiveCrowns::restart() {
    reset();
    start();
}

/**********************************************************************
 * Function Name:
 * Purpose:
 * Parameters:
 *
 * Return Value:
 * Local Variables:
 *
 * Algorithm:
 *               1)
 * Assistance Received: None
 **********************************************************************/
void FiveCrowns::reset() {
    delete game;
}

/**********************************************************************
 * Function Name:
 * Purpose:
 * Parameters:
 *
 * Return Value:
 * Local Variables:
 *
 * Algorithm:
 *               1)
 * Assistance Received: None
 **********************************************************************/
// initializes the round number
void FiveCrowns::init(int roundNumber) {
    game = new Game(roundNumber);
}
