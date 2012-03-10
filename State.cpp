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

	return moves;
}

void State::removeMove(int i){

	moves.erase(moves.begin()+i);

}

void State::print(){
	std::cout << " \n\n\n ";


	// Print the Board
	for (int i = 1; i <= (11 * 11); i++) {
		switch (get_hex_colour(i)) {
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
	std::cout << "------------------------------" << std::endl;


}


