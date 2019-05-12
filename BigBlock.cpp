using namespace std;

class BigBlock{
public:
    int b_id[4];

    BigBlock(int topleft, int topright, int bottomleft, int bottomright);
};

BigBlock::BigBlock(int topleft, int topright, int bottomleft, int bottomright){
    b_id[0] = topleft;
    b_id[1] = topright;
    b_id[2] = bottomleft;
    b_id[3] = bottomright;
}
