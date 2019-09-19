//
// Created by bibhash on 9/11/19.
//

#ifndef FIVE_CROWNS_CPP_GAME_HPP
#define FIVE_CROWNS_CPP_GAME_HPP


#include "Player.hpp"
#include "Human.hpp"
#include "Computer.hpp"
#include "Round.hpp"
#include "Utilities.hpp"

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>

class Game {
public:
    Game();
    Game(int roundNumber);
    ~Game();
    void load(vector<string> info);
    void start();
    int toss();

//    string toLowerCase(string const& str) {
//        string temp;
//
//        for (char c : str) {
//            temp.push_back(tolower(c));
//        }
//
//        return temp;
//    }
//
//    bool isEqual(string const& str, string const& str2){
//        cout << "isEqual called" << endl;
//
//        if (str.size() != str2.size()) {
//            cout << str << str2;
//            return false;
//        }
//
//        for (int i = 0; i < str.size(); ++i){
//            if (str[i] != str2[i]) {
//                cout << str[i] << str2[i];
//                return false;
//
//            }
//        }
//
//        return true;
//    }

private:
    int roundNumber;
    Player* player[2];

};


#endif //FIVE_CROWNS_CPP_GAME_HPP
