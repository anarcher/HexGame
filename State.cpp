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