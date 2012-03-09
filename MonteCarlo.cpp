/*
 * File:   MonteCarlo.cpp
 * Author: Jonathan Bibas
 *
 * Created on 06 March 2012, 14:18
 */

#include "MonteCarlo.h"
using namespace std;

/* Destructor */
MonteCarlo::~MonteCarlo(){

}

/* Returns a pair (best score, best move) using AB-pruned negamax.
 * Takes a board, maximum depth, and alpha and beta values as parameters.
 *  */
pair<double, int> MonteCarlo::getBestMove(HexBoard &board) {


	double bestResult = NEGINF;
	int bestMove = 0;
	for(int i =0 ; i < SIZE*SIZE; i++){
		if(board.S.get_hex_colour(currentMove) != State::BLANK){
			int currentResult = this->numberOfWins(board.S, firstmove);
			if(currentResult > bestResult){
				bestResult = currentResult;
				bestMove = i;
			}
		}
	}
	return bestMove;

}

//recursive 1 if won 0 if lost
bool MonteCarlo::GameResult(State &state, State::Player player){

	bool computerWon = false;
	bool humanWon = false;
	if (state.hasWon() == State::COMPUTER) {
		computerWon = true;
		return false;
	}
	if (state.hasWon() == State::HUMAN) {
		humanWon = true;
		return true;
	}

	int randomMove = rand() * (SIZE*SIZE);
	while(S.get_hex_colour(randomMove) != State::BLANK){
		randomMove = rand() *(SIZE*SIZE);
	}
	board.S.set_hex_colour(randomMove, player);

	/* Change of player */
	if(player== State::COMPUTER){
		player = State::HUMAN;
	}else if(player== State::HUMAN){
		player = State::COMPUTER;
	}
	GameResult(state, player);

}

/* Returns the result of number of won game - losts move for a given first candidate Move. */
int MonteCarlo::numberOfWins(State state, int firstmove) {


	int result = 0;
	for(int i =0 ; i < 20000; i++){
		State state = board.S;
		result += GameResult(board, firstmove, State::COMPUTER);
	}
	return result;
}
