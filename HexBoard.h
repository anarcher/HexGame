/*
 * File:   HexBoard.h
 * Author: Pit Apps
 *
 * Created on 18 February 2012, 12:59
 */

#ifndef HEXBOARD_H
#define	HEXBOARD_H
#include "HexGraph.h"
const int SIZE = 11;

class HexBoard {
public:
    HexBoard();

    HexBoard(HexGraph G, int turns) : G(G), turns(turns) {
    };
    void print();
    void putPiece(int x, int y);
    HexGraph::HexCol hasWon();
    void reset();
    void playNext();

    bool isFinished();
    HexBoard makemove(int move);
    std::vector<int> getMoves();
private:
    HexGraph G;
    int turns;
    typedef HexGraph::WHITE COMPUTER;
    typedef HexGraph::BLACK HUMAN;
    typedef HexGraph::BLANK BLANK;

    inline int getNode(int row, int col);
    inline int getCol(int x);
    inline int getRow(int x);
};

#endif	/* HEXBOARD_H */

