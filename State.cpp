/* 
 * File:   State.cpp
 * Author: Pit Apps
 * 
 * Created on 06 March 2012, 19:52
 */

#include "State.h"
#include <algorithm>
using namespace std;

/* Sets the colour of a given vertex. */
void State::set_hex_colour(int vertex, Player c) {
    piece[vertex] = c;
    turns++;
}

/* Gets the colour of a given vertex. */
State::Player State::get_hex_colour(int vertex) {
    return piece[vertex];
}

void State::setTurns(int turns) {
    this->turns = turns;
}

int State::getTurns() {
    return turns;
}

/* Returns a vector of all possible moves. */
std::vector<int> State::getMoves() {
    return moves;
}

void State::removeMove(int i) {
    moves.erase(moves.begin() + i);
}

int State::getNextMove() {
    int move = moves.back();
    moves.pop_back();
    return move;
}

void State::fillMoves() {
    for (int i = 1; i <= (11 * 11); i++) {
        if (get_hex_colour(i) == State::BLANK) {
            moves.push_back(i);
        }
    }
}

void State::shuffleMoves() {
    std::random_shuffle(moves.begin(), moves.end());
}

bool State::movesEmpty() {
    return moves.empty();
}

/* Returns the column coordinate of a given internal node number */
int getCol(int x) {
    return (x % 11 == 0 ? 11 : x % 11);
}

/* Returns the row coordinate of a given internal node number */
int getRow(int x) {
    return ((x - 1) / 11) + 1;
}


void State::print() {
// Print the top numbers
    cout << "  ";
    for (int i = 1; i <= 11; i++) {
        cout << i << "  ";
    }
    cout << endl << "1 ";

    // Print the Board
    for (int i = 1; i <= (11 * 11); i++) {
        switch (get_hex_colour(i)) {
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
         if (getCol(i) == 11 && getRow(i) != 11) {
            cout << "\n" << getRow(i + 1);
            cout.width(getRow(i) + 4);
        }
    }
    cout << endl;
    std::cout << "------------------------------" << std::endl;


}

