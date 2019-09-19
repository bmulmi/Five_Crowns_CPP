//
// Created by bibhash on 9/10/19.
//

#include "Cards.hpp"

Cards::Cards() {
    this->face = "";
    this->suite = "";
}

Cards::Cards(string& face, string &suite) {
    this->face = face;
    this->suite = suite;
}

Cards::~Cards() {

}

bool Cards::isJoker() {
    if (this->face == "J" && (this->suite == "1" || this->suite == "2" || this->suite == "3")) {
        return true;
    }
    else {
        return false;
    }
}

int Cards::getFaceValue() {
    string temp = this->face;

    if (this->isJoker()) return 50;

    if (temp == "J") return 11;
    else if (temp == "Q") return 12;
    else if (temp == "K") return 13;
    else return stoi(temp);
}