#include <iostream>
#include <string>
#include <vector>
#include "Piece.cpp"
#include "Block.cpp"
#include "BigBlock.cpp"
using namespace std;

Piece puzzle[16] =
    {Piece("Y", 0, 0, 0, 0), //00
     Piece("I", 0, 0, 0, 1), //01
     Piece("I", 0, 0, 1, 0), //02
     Piece("A", 0, 0, 1, 1), //03
     Piece("E", 0, 1, 0, 0), //04
     Piece("R", 0, 1, 0, 1), //05
     Piece("N", 0, 1, 1, 0), //06
     Piece("F", 0, 1, 1, 1), //07
     Piece("I", 1, 0, 0, 0), //08
     Piece("S", 1, 0, 0, 1), //09
     Piece("B", 1, 0, 1, 0), //10
     Piece("H", 1, 0, 1, 1), //11
     Piece("T", 1, 1, 0, 0), //12
     Piece("L", 1, 1, 0, 1), //13
     Piece("L", 1, 1, 1, 0), //14
     Piece("A", 1, 1, 1, 1)  //15
    };

void printVec(vector<int> &_vec){
    for(auto v: _vec){
        cout << v << endl;
    }
}

void printBlock(Block _block){
    string output = to_string(_block.id[0]) + " " + to_string(_block.id[1]) + " " + to_string(_block.id[2]) + " " + to_string(_block.id[3]);
    cout << output << endl;
}

void print4Blocks(vector<BigBlock> &_vec, vector<Block> &_blocks){
    for(BigBlock v: _vec){
        cout << "Answer" << endl;
        printBlock(_blocks[v.b_id[0]]);
        printBlock(_blocks[v.b_id[1]]);
        printBlock(_blocks[v.b_id[2]]);
        printBlock(_blocks[v.b_id[3]]);
    }
}

void addNeighbours(Piece (&_puzzle)[16]){
    for(int i = 0; i < 15; i++){
        for(int j = i + 1; j < 16; j++){
            if(_puzzle[i].bit[0] == _puzzle[j].bit[2] && _puzzle[i].bit[1] == _puzzle[j].bit[3]){
                _puzzle[i].top.push_back(j);
                _puzzle[j].bottom.push_back(i);
            }
            if(_puzzle[i].bit[1] == _puzzle[j].bit[0] && _puzzle[i].bit[3] == _puzzle[j].bit[2]){
                _puzzle[i].right.push_back(j);
                _puzzle[j].left.push_back(i);
            }
            if(_puzzle[i].bit[2] == _puzzle[j].bit[0] && _puzzle[i].bit[3] == _puzzle[j].bit[1]){
                _puzzle[i].bottom.push_back(j);
                _puzzle[j].top.push_back(i);
            }
            if(_puzzle[i].bit[0] == _puzzle[j].bit[1] && _puzzle[i].bit[2] == _puzzle[j].bit[3]){
                _puzzle[i].left.push_back(j);
                _puzzle[j].right.push_back(i);
            }
        }
    }

    for(int i = 0; i < 16; i++){
        cout << "puzzle["+ to_string(i) + "] top" << endl;
        printVec(_puzzle[i].top);
        cout << "puzzle["+ to_string(i) + "] bottom" << endl;
        printVec(_puzzle[i].bottom);
        cout << "puzzle["+ to_string(i) + "] left" << endl;
        printVec(_puzzle[i].left);
        cout << "puzzle["+ to_string(i) + "] right" << endl;
        printVec(_puzzle[i].right);
    }
}

void arrange4Pieces(Piece (&_puzzle)[16], vector<Block> &_blocks){
    for(int i = 0; i < 16; i++){
        int tmp_block[4];
        tmp_block[0] = i;
        for(int right: _puzzle[i].right){
            tmp_block[1] = right;
            for(int diagonal: _puzzle[right].bottom){
                if(diagonal != tmp_block[0]){
                    tmp_block[3] = diagonal;
                    for(int bottom: _puzzle[diagonal].left){
                        if(bottom != tmp_block[0] && bottom != tmp_block[1]){
                            if(_puzzle[bottom].bit[0] == _puzzle[tmp_block[0]].bit[2] && _puzzle[bottom].bit[1] == _puzzle[tmp_block[0]].bit[3]){
                                tmp_block[2] = bottom;
                                Block block = Block(tmp_block[0], tmp_block[1], tmp_block[2], tmp_block[3]);
                                _blocks.push_back(block);
                            }
                        }
                    }
                }
            }
        }
    }
}

bool BoolDuplicatePieces(Block _block1, Block _block2){
    bool duplicated = false;
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            if(_block1.id[i] == _block2.id[j]){
                duplicated = true;
            }
        }
    }
    return duplicated;
}

void addNeighbourBlock(Piece (&_puzzle)[16], vector<Block> &_blocks){
    for(int i = 0; i < (_blocks.size() - 1); i++){
        //top, left, bottom, right
        int bit_pair_subject[4] =
            {   1000 * _puzzle[_blocks[i].id[0]].bit[0] +
                100 * _puzzle[_blocks[i].id[0]].bit[1] +
                10 * _puzzle[_blocks[i].id[1]].bit[0] + _puzzle[_blocks[i].id[1]].bit[1],
                1000 * _puzzle[_blocks[i].id[0]].bit[0] +
                100 * _puzzle[_blocks[i].id[0]].bit[2] +
                10 * _puzzle[_blocks[i].id[2]].bit[0] + _puzzle[_blocks[i].id[2]].bit[2],
                1000 * _puzzle[_blocks[i].id[2]].bit[2] +
                100 * _puzzle[_blocks[i].id[2]].bit[3] +
                10 * _puzzle[_blocks[i].id[3]].bit[2] + _puzzle[_blocks[i].id[3]].bit[3],
                1000 * _puzzle[_blocks[i].id[1]].bit[1] +
                100 * _puzzle[_blocks[i].id[1]].bit[3] +
                10 * _puzzle[_blocks[i].id[3]].bit[1] + _puzzle[_blocks[i].id[3]].bit[3]};
        for(int j = i + 1; j < _blocks.size(); j++){
            if(!BoolDuplicatePieces(_blocks[i], _blocks[j])){
                int bit_pair_object[4] =
                    {   1000 * _puzzle[_blocks[j].id[0]].bit[0] +
                        100 * _puzzle[_blocks[j].id[0]].bit[1] +
                        10 * _puzzle[_blocks[j].id[1]].bit[0] + _puzzle[_blocks[j].id[1]].bit[1],
                        1000 * _puzzle[_blocks[j].id[0]].bit[0] +
                        100 * _puzzle[_blocks[j].id[0]].bit[2] +
                        10 * _puzzle[_blocks[j].id[2]].bit[0] + _puzzle[_blocks[j].id[2]].bit[2],
                        1000 * _puzzle[_blocks[j].id[2]].bit[2] +
                        100 * _puzzle[_blocks[j].id[2]].bit[3] +
                        10 * _puzzle[_blocks[j].id[3]].bit[2] + _puzzle[_blocks[j].id[3]].bit[3],
                        1000 * _puzzle[_blocks[j].id[1]].bit[1] +
                        100 * _puzzle[_blocks[j].id[1]].bit[3] +
                        10 * _puzzle[_blocks[j].id[3]].bit[1] + _puzzle[_blocks[j].id[3]].bit[3]};
                if(bit_pair_subject[0] == bit_pair_object[2]){
                    _blocks[i].top.push_back(j);
                    _blocks[j].bottom.push_back(i);
                }
                if(bit_pair_subject[3] == bit_pair_object[1]){
                    _blocks[i].right.push_back(j);
                    _blocks[j].left.push_back(i);
                }
                if(bit_pair_subject[2] == bit_pair_object[0]){
                    _blocks[i].bottom.push_back(j);
                    _blocks[j].top.push_back(i);
                }
                if(bit_pair_subject[1] == bit_pair_object[3]){
                    _blocks[i].left.push_back(j);
                    _blocks[j].right.push_back(i);
                }
            }
        }
    }

    for(int i = 0; i < _blocks.size(); i++){
        cout << "_blocks["+ to_string(i) + "] top" << endl;
        printVec(_blocks[i].top);
        cout << "_blocks["+ to_string(i) + "] bottom" << endl;
        printVec(_blocks[i].bottom);
        cout << "_blocks["+ to_string(i) + "] left" << endl;
        printVec(_blocks[i].left);
        cout << "_blocks["+ to_string(i) + "] right" << endl;
        printVec(_blocks[i].right);
    }
}

void arrange4Blocks(Piece (&_puzzle)[16], vector<Block> &_blocks, vector<BigBlock> &_bigblocks){
    for(int i = 0; i < _blocks.size(); i++){
        int tmp_bigblock[4];
        tmp_bigblock[0] = i;
        for(int right: _blocks[i].right){
            tmp_bigblock[1] = right;
            for(int diagonal: _blocks[right].bottom){
                if(!BoolDuplicatePieces(_blocks[diagonal], _blocks[tmp_bigblock[0]])){
                    tmp_bigblock[3] = diagonal;
                    for(int bottom: _blocks[diagonal].left){
                        if(!BoolDuplicatePieces(_blocks[bottom], _blocks[tmp_bigblock[0]]) && !BoolDuplicatePieces(_blocks[bottom], _blocks[tmp_bigblock[1]])){
                            int object_bigblock_top =
                                1000 * _puzzle[_blocks[bottom].id[0]].bit[0] +
                                100 * _puzzle[_blocks[bottom].id[0]].bit[1] +
                                10 * _puzzle[_blocks[bottom].id[1]].bit[0] + _puzzle[_blocks[bottom].id[1]].bit[1];
                            int subject_bigblock_bottom =
                                1000 * _puzzle[_blocks[tmp_bigblock[0]].id[2]].bit[2] +
                                100 * _puzzle[_blocks[tmp_bigblock[0]].id[2]].bit[3] +
                                10 * _puzzle[_blocks[tmp_bigblock[0]].id[3]].bit[2] + _puzzle[_blocks[tmp_bigblock[0]].id[3]].bit[3];
                            if(object_bigblock_top == subject_bigblock_bottom){
                                tmp_bigblock[2] = bottom;
                                BigBlock bigblock = BigBlock(tmp_bigblock[0], tmp_bigblock[1], tmp_bigblock[2], tmp_bigblock[3]);
                                _bigblocks.push_back(bigblock);
                            }
                        }
                    }
                }
            }
        }
    }
}

void printCharacter(Piece _piece){
    cout << _piece.character << endl;
}

void printAnswerPhrases(Piece (&_puzzle)[16], vector<Block> &_blocks, vector<BigBlock> &_bigblocks){
    int count = 1;
    for(BigBlock bb: _bigblocks){
        string piece_char[4][4];
        piece_char[0][3] = _puzzle[_blocks[bb.b_id[0]].id[0]].character;
        piece_char[0][2] = _puzzle[_blocks[bb.b_id[0]].id[1]].character;
        piece_char[1][3] = _puzzle[_blocks[bb.b_id[0]].id[2]].character;
        piece_char[1][2] = _puzzle[_blocks[bb.b_id[0]].id[3]].character;
        piece_char[0][1] = _puzzle[_blocks[bb.b_id[1]].id[0]].character;
        piece_char[0][0] = _puzzle[_blocks[bb.b_id[1]].id[1]].character;
        piece_char[1][1] = _puzzle[_blocks[bb.b_id[1]].id[2]].character;
        piece_char[1][0] = _puzzle[_blocks[bb.b_id[1]].id[3]].character;
        piece_char[2][3] = _puzzle[_blocks[bb.b_id[2]].id[0]].character;
        piece_char[2][2] = _puzzle[_blocks[bb.b_id[2]].id[1]].character;
        piece_char[3][3] = _puzzle[_blocks[bb.b_id[2]].id[2]].character;
        piece_char[3][2] = _puzzle[_blocks[bb.b_id[2]].id[3]].character;
        piece_char[2][1] = _puzzle[_blocks[bb.b_id[3]].id[0]].character;
        piece_char[2][0] = _puzzle[_blocks[bb.b_id[3]].id[1]].character;
        piece_char[3][1] = _puzzle[_blocks[bb.b_id[3]].id[2]].character;
        piece_char[3][0] = _puzzle[_blocks[bb.b_id[3]].id[3]].character;

        string phrase;
        for(int i = 0; i < 4; i++){
            for(int j = 0; j < 4; j++){
                phrase.append(piece_char[i][j]);
            }
        }
        cout << phrase << endl;
        count++;
    }
    cout << count << endl;
}

void printPiecePattern(Piece (&_puzzle)[16], vector<Block> &_blocks, vector<BigBlock> &_bigblocks){
    for(BigBlock bb:_bigblocks){
        int piece[8][8];
        //topleft bigblock
        piece[0][0] = _puzzle[_blocks[bb.b_id[0]].id[0]].bit[0];
        piece[0][1] = _puzzle[_blocks[bb.b_id[0]].id[0]].bit[1];
        piece[1][0] = _puzzle[_blocks[bb.b_id[0]].id[0]].bit[2];
        piece[1][1] = _puzzle[_blocks[bb.b_id[0]].id[0]].bit[3];
        piece[0][2] = _puzzle[_blocks[bb.b_id[0]].id[1]].bit[0];
        piece[0][3] = _puzzle[_blocks[bb.b_id[0]].id[1]].bit[1];
        piece[1][2] = _puzzle[_blocks[bb.b_id[0]].id[1]].bit[2];
        piece[1][3] = _puzzle[_blocks[bb.b_id[0]].id[1]].bit[3];
        piece[2][0] = _puzzle[_blocks[bb.b_id[0]].id[2]].bit[0];
        piece[2][1] = _puzzle[_blocks[bb.b_id[0]].id[2]].bit[1];
        piece[3][0] = _puzzle[_blocks[bb.b_id[0]].id[2]].bit[2];
        piece[3][1] = _puzzle[_blocks[bb.b_id[0]].id[2]].bit[3];
        piece[2][2] = _puzzle[_blocks[bb.b_id[0]].id[3]].bit[0];
        piece[2][3] = _puzzle[_blocks[bb.b_id[0]].id[3]].bit[1];
        piece[3][2] = _puzzle[_blocks[bb.b_id[0]].id[3]].bit[2];
        piece[3][3] = _puzzle[_blocks[bb.b_id[0]].id[3]].bit[3];
        //topright bigblock
        piece[0][4] = _puzzle[_blocks[bb.b_id[1]].id[0]].bit[0];
        piece[0][5] = _puzzle[_blocks[bb.b_id[1]].id[0]].bit[1];
        piece[1][4] = _puzzle[_blocks[bb.b_id[1]].id[0]].bit[2];
        piece[1][5] = _puzzle[_blocks[bb.b_id[1]].id[0]].bit[3];
        piece[0][6] = _puzzle[_blocks[bb.b_id[1]].id[1]].bit[0];
        piece[0][7] = _puzzle[_blocks[bb.b_id[1]].id[1]].bit[1];
        piece[1][6] = _puzzle[_blocks[bb.b_id[1]].id[1]].bit[2];
        piece[1][7] = _puzzle[_blocks[bb.b_id[1]].id[1]].bit[3];
        piece[2][4] = _puzzle[_blocks[bb.b_id[1]].id[2]].bit[0];
        piece[2][5] = _puzzle[_blocks[bb.b_id[1]].id[2]].bit[1];
        piece[3][4] = _puzzle[_blocks[bb.b_id[1]].id[2]].bit[2];
        piece[3][5] = _puzzle[_blocks[bb.b_id[1]].id[2]].bit[3];
        piece[2][6] = _puzzle[_blocks[bb.b_id[1]].id[3]].bit[0];
        piece[2][7] = _puzzle[_blocks[bb.b_id[1]].id[3]].bit[1];
        piece[3][6] = _puzzle[_blocks[bb.b_id[1]].id[3]].bit[2];
        piece[3][7] = _puzzle[_blocks[bb.b_id[1]].id[3]].bit[3];
        //bottomleft bigblock
        piece[4][0] = _puzzle[_blocks[bb.b_id[2]].id[0]].bit[0];
        piece[4][1] = _puzzle[_blocks[bb.b_id[2]].id[0]].bit[1];
        piece[5][0] = _puzzle[_blocks[bb.b_id[2]].id[0]].bit[2];
        piece[5][1] = _puzzle[_blocks[bb.b_id[2]].id[0]].bit[3];
        piece[4][2] = _puzzle[_blocks[bb.b_id[2]].id[1]].bit[0];
        piece[4][3] = _puzzle[_blocks[bb.b_id[2]].id[1]].bit[1];
        piece[5][2] = _puzzle[_blocks[bb.b_id[2]].id[1]].bit[2];
        piece[5][3] = _puzzle[_blocks[bb.b_id[2]].id[1]].bit[3];
        piece[6][0] = _puzzle[_blocks[bb.b_id[2]].id[2]].bit[0];
        piece[6][1] = _puzzle[_blocks[bb.b_id[2]].id[2]].bit[1];
        piece[7][0] = _puzzle[_blocks[bb.b_id[2]].id[2]].bit[2];
        piece[7][1] = _puzzle[_blocks[bb.b_id[2]].id[2]].bit[3];
        piece[6][2] = _puzzle[_blocks[bb.b_id[2]].id[3]].bit[0];
        piece[6][3] = _puzzle[_blocks[bb.b_id[2]].id[3]].bit[1];
        piece[7][2] = _puzzle[_blocks[bb.b_id[2]].id[3]].bit[2];
        piece[7][3] = _puzzle[_blocks[bb.b_id[2]].id[3]].bit[3];
        //bottomright bigblock
        piece[4][4] = _puzzle[_blocks[bb.b_id[3]].id[0]].bit[0];
        piece[4][5] = _puzzle[_blocks[bb.b_id[3]].id[0]].bit[1];
        piece[5][4] = _puzzle[_blocks[bb.b_id[3]].id[0]].bit[2];
        piece[5][5] = _puzzle[_blocks[bb.b_id[3]].id[0]].bit[3];
        piece[4][6] = _puzzle[_blocks[bb.b_id[3]].id[1]].bit[0];
        piece[4][7] = _puzzle[_blocks[bb.b_id[3]].id[1]].bit[1];
        piece[5][6] = _puzzle[_blocks[bb.b_id[3]].id[1]].bit[2];
        piece[5][7] = _puzzle[_blocks[bb.b_id[3]].id[1]].bit[3];
        piece[6][4] = _puzzle[_blocks[bb.b_id[3]].id[2]].bit[0];
        piece[6][5] = _puzzle[_blocks[bb.b_id[3]].id[2]].bit[1];
        piece[7][4] = _puzzle[_blocks[bb.b_id[3]].id[2]].bit[2];
        piece[7][5] = _puzzle[_blocks[bb.b_id[3]].id[2]].bit[3];
        piece[6][6] = _puzzle[_blocks[bb.b_id[3]].id[3]].bit[0];
        piece[6][7] = _puzzle[_blocks[bb.b_id[3]].id[3]].bit[1];
        piece[7][6] = _puzzle[_blocks[bb.b_id[3]].id[3]].bit[2];
        piece[7][7] = _puzzle[_blocks[bb.b_id[3]].id[3]].bit[3];

        cout << "pattern" << endl;
        for(int i = 0; i < 8; i++){
            cout << piece[i][0] << piece[i][1] << " " << piece[i][2] << piece[i][3] << " " << piece[i][4] << piece[i][5] << " " << piece[i][6] << piece[i][7] << endl;
            if(i % 2 == 1){
                cout << " " << endl;
            }
        }

        int piece_num[4][4];
        piece_num[0][0] = _blocks[bb.b_id[0]].id[0];
        piece_num[0][1] = _blocks[bb.b_id[0]].id[1];
        piece_num[1][0] = _blocks[bb.b_id[0]].id[2];
        piece_num[1][1] = _blocks[bb.b_id[0]].id[3];
        piece_num[0][2] = _blocks[bb.b_id[1]].id[0];
        piece_num[0][3] = _blocks[bb.b_id[1]].id[1];
        piece_num[1][2] = _blocks[bb.b_id[1]].id[2];
        piece_num[1][3] = _blocks[bb.b_id[1]].id[3];
        piece_num[2][0] = _blocks[bb.b_id[2]].id[0];
        piece_num[2][1] = _blocks[bb.b_id[2]].id[1];
        piece_num[3][0] = _blocks[bb.b_id[2]].id[2];
        piece_num[3][1] = _blocks[bb.b_id[2]].id[3];
        piece_num[2][2] = _blocks[bb.b_id[3]].id[0];
        piece_num[2][3] = _blocks[bb.b_id[3]].id[1];
        piece_num[3][2] = _blocks[bb.b_id[3]].id[2];
        piece_num[3][3] = _blocks[bb.b_id[3]].id[3];

        cout << "piece_num" << endl;
        for(int i = 0; i < 4; i++){
            cout << piece_num[i][0] << " " << piece_num[i][1] << " " << piece_num[i][2] << " " << piece_num[i][3] << endl;
        }
        cout << " " << endl;
    }
}

void printAnswerStringMatrix(Piece (&_puzzle)[16], vector<Block> &_blocks, vector<BigBlock> &_bigblocks){
    for(BigBlock bb:_bigblocks){
        string piece_num[4][4];
        piece_num[0][3] = _puzzle[_blocks[bb.b_id[0]].id[0]].character;
        piece_num[0][2] = _puzzle[_blocks[bb.b_id[0]].id[1]].character;
        piece_num[1][3] = _puzzle[_blocks[bb.b_id[0]].id[2]].character;
        piece_num[1][2] = _puzzle[_blocks[bb.b_id[0]].id[3]].character;
        piece_num[0][1] = _puzzle[_blocks[bb.b_id[1]].id[0]].character;
        piece_num[0][0] = _puzzle[_blocks[bb.b_id[1]].id[1]].character;
        piece_num[1][1] = _puzzle[_blocks[bb.b_id[1]].id[2]].character;
        piece_num[1][0] = _puzzle[_blocks[bb.b_id[1]].id[3]].character;
        piece_num[2][3] = _puzzle[_blocks[bb.b_id[2]].id[0]].character;
        piece_num[2][2] = _puzzle[_blocks[bb.b_id[2]].id[1]].character;
        piece_num[3][3] = _puzzle[_blocks[bb.b_id[2]].id[2]].character;
        piece_num[3][2] = _puzzle[_blocks[bb.b_id[2]].id[3]].character;
        piece_num[2][1] = _puzzle[_blocks[bb.b_id[3]].id[0]].character;
        piece_num[2][0] = _puzzle[_blocks[bb.b_id[3]].id[1]].character;
        piece_num[3][1] = _puzzle[_blocks[bb.b_id[3]].id[2]].character;
        piece_num[3][0] = _puzzle[_blocks[bb.b_id[3]].id[3]].character;

        for(int i = 0; i < 4; i++){
            cout << piece_num[i][0] << " " << piece_num[i][1] << " " << piece_num[i][2] << " " << piece_num[i][3] << endl;
        }
        cout << " " << endl;
    }
}
int main(){
    addNeighbours(puzzle);

    vector<Block> blocks;
    arrange4Pieces(puzzle, blocks);
    for(Block b: blocks){
        printBlock(b);
    }
    cout << "blocks.size() = " << blocks.size() << endl;

    addNeighbourBlock(puzzle, blocks);
    vector<BigBlock> bigblocks;
    arrange4Blocks(puzzle, blocks, bigblocks);
    cout << "bigblocks.size() = " << bigblocks.size() << endl;
    print4Blocks(bigblocks, blocks);

    printPiecePattern(puzzle, blocks, bigblocks);
    // printAnswerStringMatrix(puzzle, blocks, bigblocks);
    printAnswerPhrases(puzzle, blocks, bigblocks);
}
