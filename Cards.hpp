//
// Created by bibhash on 9/10/19.
//

#ifndef FIVE_CROWNS_CPP_CARDS_HPP
#define FIVE_CROWNS_CPP_CARDS_HPP

#include <string>
using namespace std;

class Cards {
public:
    Cards() = default;
    Cards(string& face, string& suit);
    ~Cards() = default;
    friend bool operator==(const Cards &left, const Cards &right);

    const int getFaceValue();
    const string getSuite() { return suite; }
    const string getFace() { return face; }
    const string toString() { return face + suite; }

    bool isJoker();

private:
    string face;
    string suite;
};


#endif //FIVE_CROWNS_CPP_CARDS_H
