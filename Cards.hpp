//
// Created by bibhash on 9/10/19.
//

#ifndef FIVE_CROWNS_CPP_CARDS_HPP
#define FIVE_CROWNS_CPP_CARDS_HPP

#include <string>
using namespace std;

class Cards {
public:
    Cards();
    Cards(string& face, string& suit);
    ~Cards();

    string getSuit() { return suite; }
    string getFace() { return face; }
    string toString() { return face + suite; }

private:
    string face;
    string suite;
};


#endif //FIVE_CROWNS_CPP_CARDS_H
