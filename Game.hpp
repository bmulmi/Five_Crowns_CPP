//
// Created by bibhash on 9/11/19.
//

#ifndef FIVE_CROWNS_CPP_GAME_HPP
#define FIVE_CROWNS_CPP_GAME_HPP


#include "Player.hpp"
#include "Human.hpp"
#include "Computer.hpp"
#include "Round.hpp"

#include <iostream>
#include <cstdlib>
#include <ctime>

class Game {
public:
    Game();
    Game(int roundNumber);
    ~Game();
    void load(vector<string> info);
    void start();
    int toss();

    string toLowerCase(string str) {
        string temp;

        for (char c : str) {
            temp.push_back(tolower(c));
        }

        return temp;
    }

    bool isEqual(string str, string str2){
        if (str.size() != str2.size()) return false;

        for (int i = 0; i < str.size(); i++){
            if (str[i] != str2[i]) return false;
        }

        return true;
    }

private:
    int roundNumber;
    Player* player[2];

};


#endif //FIVE_CROWNS_CPP_GAME_HPP
