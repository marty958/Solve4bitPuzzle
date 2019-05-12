#include <iostream>
using namespace std;

class Block{
public:
    int id[4];
    vector<int> right;
    vector<int> left;
    vector<int> top;
    vector<int> bottom;

    Block(int topleft, int topright, int bottomleft, int bottomright);
};

Block::Block(int topleft, int topright, int bottomleft, int bottomright){
    id[0] = topleft;
    id[1] = topright;
    id[2] = bottomleft;
    id[3] = bottomright;
}
