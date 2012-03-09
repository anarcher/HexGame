/* 
 * File:   State.cpp
 * Author: Pit Apps
 * 
 * Created on 06 March 2012, 19:52
 */

#include "State.h"

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
    std::vector<int> moves;
    for (int i = 1; i <= 121; i++) {
        if (get_hex_colour(i) == State::BLANK) {
            moves.push_back(i);
        }
    }
    return moves;
}