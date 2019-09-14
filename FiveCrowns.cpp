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

    string filename;
    if (load == 'y') {
        loadGame();
    }
    else {
        init(1);
        game->start();
    }
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
    string file = "/home/bibhash/git_repos/Five_Crowns_CPP/";

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
    getline(save, line);
    int roundNumber = stoi(Utilities::getValue(line));

    vector<string> roundStats;
    while(getline(save, line)) {
        if(!line.empty() || line != "") {
            string val = Utilities::getValue(line);
            roundStats.push_back(Utilities::trim(val));
        }
    }

    init(roundNumber);
    game->load(roundStats);
}
