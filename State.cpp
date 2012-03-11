/* 
 * File:   State.cpp
 * Author: Pit Apps
 * 
 * Created on 06 March 2012, 19:52
 */

#include "State.h"

/* Sets the colour of a given vertex. */
void State::set_hex_colour(int vertex, Player c) {
    piece.at(vertex) = c;
    turns++;
}

/* Gets the colour of a given vertex. */
State::Player State::get_hex_colour(int vertex) {
    return piece.at(vertex);
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
            moves.push_back(i); //logical error why starts at 3?? should start at 2! (if human begins with (1, 1))
        }
    }

}

int State::getSize() {
    return moves.size();
}

void State::print() {
    std::cout << " \n\n\n ";


    // Print the Board
    for (int i = 1; i <= 11; i++) {
        for (int y = 1; y <= 11; y++) {
            switch (get_hex_colour((i) + (y - 1)*11)) {
                case State::BLANK:
                    std::cout << " E ";
                    break;
                case State::HUMAN:
                    std::cout << " B ";
                    break;
                case State::COMPUTER:
                    std::cout << " W ";
                    break;
            }
        }
        std::cout << "\n " << std::endl;
    }
    std::cout << "------------------------------" << std::endl;


}


