/*
 * File:   HexBoard.cpp
 * Author: Pit Apps
 *
 * Created on 18 February 2012, 12:59
 */
#include "HexBoard.h"
#include <ctime>
#include <cstdlib>
using namespace std;

/* Constructor for a HexBoard. Also sets turns to 0, which is used for the hasWon() method */
HexBoard::HexBoard() {
    for (int i = 1; i <= SIZE; i++) {
        for (int j = 1; j <= SIZE; j++) {
            if (getCol(j) != SIZE) {
                G.add_edge(getNode(i, j), getNode(i, j + 1)); //left to right
            }
            if (i != SIZE) {
                G.add_edge(getNode(i, j), getNode(i + 1, j)); //up to direct under
                if (getCol(j) != 1) {
                    G.add_edge(getNode(i, j), getNode(i + 1, j - 1)); //up to left under
                }
            }
        }
    }
    turns = 0;
    Player = HexGraph::HUMAN;
}

HexBoard::HexBoard(HexGraph &G, int turns){
    this->G = G;
    this->turns = turns;
}

/* Returns the internal node number for a node at a given coordinate */
int HexBoard::getNode(int row, int col) {
    return ((SIZE * (row - 1)) + col);
}

/* Returns the column coordinate of a given internal node number */
int HexBoard::getCol(int x) {
    return (x % SIZE == 0 ? SIZE : x % SIZE);
}

/* Returns the row coordinate of a given internal node number */
int HexBoard::getRow(int x) {
    return ((x - 1) / SIZE) + 1;
}

/* Puts a black piece on a given coordinate */
void HexBoard::putPiece(int x, int y) {
    int node = getNode(x, y);

    // Make sure the Node is legal
    if (node > (SIZE * SIZE) || node < 1) {
        throw 1;
    }
    if (G.get_hex_colour(node) != HexGraph::BLANK) {
        throw 2;
    }

    G.set_hex_colour(getNode(x, y), HexGraph::HUMAN);
    switchPlayer();
    turns++;
}

/* Prints the Hex Board */
void HexBoard::print() {
    // Print the top numbers
    cout << "  ";
    for (int i = 1; i <= SIZE; i++) {
        cout << i << "  ";
    }
    cout << endl << "1 ";

    // Print the Board
    for (int i = 1; i <= (SIZE * SIZE); i++) {
        switch (G.get_hex_colour(i)) {
            case HexGraph::BLANK:
                cout << " E ";
                break;
            case HexGraph::HUMAN:
                cout << " B ";
                break;
            case HexGraph::COMPUTER:
                cout << " W ";
                break;
        }

        // Print left side numbers
        if (getCol(i) == SIZE && getRow(i) != SIZE) {
            cout << "\n" << getRow(i + 1);
            cout.width(getRow(i) + 4);
        }
    }
    cout << endl;
}

/* Returns the winner, or blank when there is no winner */
HexGraph::HexCol HexBoard::hasWon() {

    // If there haven't been 11 turns EACH, then there's no need to look
    if (turns >= SIZE * 2) {

        // Check if HUMAN has won (Top to Bottom)
        for (int i = 1; i <= SIZE; i++) {
            if (G.get_hex_colour(i) == HexGraph::HUMAN) {
                G.dijkstra_run(i, HexGraph::HUMAN, true);
                for (int j = getNode(SIZE, 1); j <= getNode(SIZE, SIZE); j++) {
                    if (G.get_parent(j) != NIL) {
                        return HexGraph::HUMAN;
                    }
                }
            }
        }

        // Check if COMPUTER has won (Left to Right)
        int k = 1;
        for (int i = 1; i <= (SIZE * SIZE) - (SIZE - 1); i = getNode(++k, 1)) {
            if (G.get_hex_colour(i) == HexGraph::COMPUTER) {
                G.dijkstra_run(i, HexGraph::COMPUTER, true);
                for (int j = getNode(1, SIZE); j <= getNode(SIZE, SIZE); j = getNode(getRow(j) + 1, SIZE)) {
                    if (G.get_parent(j) != NIL) {
                        return HexGraph::COMPUTER;
                    }
                }
            }
        }
    }
    return HexGraph::BLANK;
}

/* Resets the board to a blank state */
void HexBoard::reset() {
    for (int i = 1; i <= (SIZE * SIZE); i++) {
        G.set_hex_colour(i, HexGraph::BLANK);
    }
    turns = 0;
}

/* Returns true if the game has finished */
bool HexBoard::isFinished() {
    return (hasWon() != HexGraph::BLANK);
}

/* Returns a new Board with the specified move played. */
HexBoard HexBoard::makemove(int move) {
    HexBoard HB(this->G, this->turns + 1);
    HB.G.set_hex_colour(move, Player);
    HB.switchPlayer();
    return HB;
}

/* Returns a vector of all possible moves. */
vector<int> HexBoard::getMoves() {
    vector<int> moves;
    for (int i = 1; i <= (SIZE * SIZE); i++) {
        if (G.get_hex_colour(i) == HexGraph::BLANK) {
            moves.push_back(i);
        }
    }
    return moves;
}

/* Switches the current player. */
void HexBoard::switchPlayer() {
    Player = (Player == HexGraph::HUMAN ? HexGraph::COMPUTER : HexGraph::HUMAN);
}

/*Returns a number evaluating the current board. */
double HexBoard::eval() {
    // Magic Code goes here!
}