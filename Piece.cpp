#include <iostream>
#include <vector>
using namespace std;

class Piece{
public:
    string character;
    int bit[4]; //topleft, topright, bottomleft, bottomright
    vector<int> right;
    vector<int> left;
    vector<int> top;
    vector<int> bottom;

    Piece(string _character, int topleft, int topright, int bottomleft, int bottomright);
};

Piece::Piece(string _character, int topleft, int topright, int bottomleft, int bottomright){
    character = _character;
    bit[0] = topleft;
    bit[1] = topright;
    bit[2] = bottomleft;
    bit[3] = bottomright;
}
