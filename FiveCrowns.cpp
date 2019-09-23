//
// Created by bibhash on 9/11/19.
//

#include "FiveCrowns.hpp"

FiveCrowns::FiveCrowns() {

}

FiveCrowns::~FiveCrowns() {
    reset();
}

void FiveCrowns::start() {
    cout << "Welcome to Five Crowns!" << endl;
    char load;
    do {
        cout << "Do you want to load game? (y/n) ";
        cin >> load;
    } while(load != 'y' && load != 'n');

    if (load == 'y') {
        loadGame();
    }
    else {
        init(1);
        game->start();
    }

    cout << "Thank you for playing Five Crowns! Hope you enjoyed it!" << endl;
}



void FiveCrowns::restart() {

}

void FiveCrowns::reset() {

}

// initializes the round number
// next player: 0 for human, 1 for computer
void FiveCrowns::init(int roundNumber) {
    game = new Game(roundNumber);
}

void FiveCrowns::loadGame() {
    string file = "/home/bibhash/git_repos/Five_Crowns_CPP/savedGames/";

    ifstream save;
    string filename;

    do{
        cin.ignore();
        cout << "What is the name of the saved file? ";
        cin >> filename;
        filename.append(".txt");
        file += filename;
        save.open(file);
    } while (!save.is_open());

    string line;
    // get the round number
    getline(save, line);
    int roundNumber = stoi(Utils::getValue(line));

    // store everything else in a vector of strings
    vector<string> roundStats;
    while(getline(save, line)) {
        if(!line.empty() || line != "") {
            string val = Utils::getValue(line);
            roundStats.push_back(Utils::trim(val));
        }
    }

    // initialize the game with the round number
    init(roundNumber);

    // load the game
    game->load(roundStats);
}
