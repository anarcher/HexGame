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
    void print();
    void putPiece(int x, int y);
    HexGraph::HexCol hasWon();
    void reset();
    void playNext();
private:
    HexGraph G;
    inline int getNode(int row, int col);
    inline int getCol(int x);
    inline int getRow(int x);

    int extendPath(HexGraph::HexCol c, std::list<int> &path);

    int turns;
};

#endif	/* HEXBOARD_H */

