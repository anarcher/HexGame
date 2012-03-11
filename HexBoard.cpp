/*
 * File:   HexBoard.cpp
 * Author: Pit Apps
 *
 * Created on 18 February 2012, 12:59
 */
#include "MonteCarlo.h"
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
    S.setTurns(0);
    Player = State::HUMAN;
}

HexBoard::HexBoard(HexGraph &G, State S, int turns) {
    this->G = G;
    this->S = S;
    this->S.setTurns(turns);
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
    if (S.get_hex_colour(node) != State::BLANK) {
        throw 2;
    }

    S.set_hex_colour(getNode(x, y), State::HUMAN);
    switchPlayer();
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
        switch (S.get_hex_colour(i)) {
            case State::BLANK:
                cout << " E ";
                break;
            case State::HUMAN:
                cout << " B ";
                break;
            case State::COMPUTER:
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

/* Resets the board to a blank state */
void HexBoard::reset() {
    for (int i = 1; i <= (SIZE * SIZE); i++) {
        S.set_hex_colour(i, State::BLANK);
    }
    S.setTurns(0);
}

/* Returns true if the game has finished */
bool HexBoard::isFinished() {
    return (hasWon() != State::BLANK);
}

/* Returns a new Board with the specified move played. */
HexBoard HexBoard::makemove(int move) {
    HexBoard HB(this->G, this->S, this->S.getTurns() + 1);
    HB.S.set_hex_colour(move, Player);
    HB.switchPlayer();
    return HB;
}

/* Returns a vector of all possible moves. */
vector<int> HexBoard::getMoves() {
    return S.getMoves();
}

/* Switches the current player. */
void HexBoard::switchPlayer() {
    Player = (Player == State::HUMAN ? State::COMPUTER : State::HUMAN);
}

State HexBoard::getState() {
    return S;
}

void HexBoard::playComputer() {
    MonteCarlo MC(this);
    int move = MC.getBestMove();
    S.set_hex_colour(move, State::COMPUTER);
}

State::Player HexBoard::hasWon() {
    return hasWon(S);
}

std::vector<int> HexBoard::getNeighborsOf(int i, State &state, State::Player wanted, vector<bool> &visited) {

    vector<int> edgeVector;
    Graph::EdList temp = G.get_edges(i);
    for (Graph::EdList::iterator it = temp.begin(); it != temp.end(); it++) {
        if (state.get_hex_colour(it->dest) == wanted && visited[it->dest] == false) {
            edgeVector.push_back(it->dest);
        }
    }

    return edgeVector;
}

/**
 *
 */
bool HexBoard::checkWon(State &state, State::Player wanted, int current, vector<bool> &visited) {

    if (wanted == State::COMPUTER) {
        if (getCol(current) == SIZE) {
            return true;
        }
    } else {
        if (getRow(current) == SIZE) {
            return true;
        }
    }

    visited[current] = true;
    vector<int> neighbors = getNeighborsOf(current, state, wanted, visited);

    if (!neighbors.empty()) {
        for (vector<int>::iterator j = neighbors.begin(); j != neighbors.end(); j++) {
            visited[*j] = true;
            return checkWon(state, wanted, *j, visited);
        }
    } else {
        return false;
    }
}

State::Player HexBoard::hasWon2() {
    return hasWon2(S);
}

State::Player HexBoard::hasWon2(State &state) {
    //if (state.getTurns() >= SIZE * 2) {
    std::vector<bool> visited((SIZE * SIZE) + 1, false);

    /* CHECK HUMAN */
    if (this->checkWon(state, State::HUMAN, 1, visited)) {
        return State::HUMAN;
    }

    visited.clear();
    visited.resize((SIZE * SIZE) + 1, false);

    /* CHECK COMPUTER */
    if (checkWon(state, State::COMPUTER, 1, visited)) {
        return State::COMPUTER;
    }
    // }
    return State::BLANK;
}

/* Returns the winner, or blank when there is no winner */
State::Player HexBoard::hasWon(State &state) {

    // If there haven't been 11 turns EACH, then there's no need to look
    if (state.getTurns() >= SIZE * 2) {

        // Check if HUMAN has won (Top to Bottom)
        for (int i = 1; i <= SIZE; i++) {
            if (state.get_hex_colour(i) == State::HUMAN) {
                G.dijkstra_run(i, State::HUMAN, state);
                for (int j = getNode(SIZE, 1); j <= getNode(SIZE, SIZE); j++) {
                    if (G.get_parent(j) != NIL) {
                        return State::HUMAN;
                    }
                }
            }
        }

        // Check if COMPUTER has won (Left to Right)
        int k = 1;
        for (int i = 1; i <= (SIZE * SIZE) - (SIZE - 1); i = getNode(++k, 1)) {
            if (state.get_hex_colour(i) == State::COMPUTER) {
                G.dijkstra_run(i, State::COMPUTER, state);
                for (int j = getNode(1, SIZE); j <= getNode(SIZE, SIZE); j = getNode(getRow(j) + 1, SIZE)) {
                    if (G.get_parent(j) != NIL) {
                        return State::COMPUTER;
                    }
                }
            }
        }
    }
    return State::BLANK;
}
