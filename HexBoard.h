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

    HexBoard(HexGraph &G, State S, int turns);
    void print();
    void putPiece(int x, int y);
    void reset();
    void playNext();

    bool isFinished();
    HexBoard makemove(int move);
    std::vector<int> getMoves();

    State getState();
    void playComputer();

    State::Player hasWon();
    State::Player hasWon(State &S);


    State::Player hasWon2();
    State::Player hasWon2(State &state);
private:
    State S;
    HexGraph G;
    State::Player Player;

    static inline int getNode(int row, int col);
    static inline int getCol(int x);
    static inline int getRow(int x);

    void switchPlayer();
    std::vector<int> getNeighboursOf(int i, State &state, State::Player wanted, std::vector<bool> &visited);
    bool checkWon(State &state, State::Player wanted, int current, std::vector<bool> &visited);

};

#endif	/* HEXBOARD_H */

