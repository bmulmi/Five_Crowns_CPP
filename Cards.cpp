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