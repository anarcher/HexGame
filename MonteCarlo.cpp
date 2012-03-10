/*
 * File:   MonteCarlo.cpp
 * Author: Jonathan Bibas
 *
 * Created on 06 March 2012, 14:18
 */

#include "MonteCarlo.h"
#include <ctime>
#include <cstdlib>
using namespace std;

int MonteCarlo::getBestMove() {

	int bestResult = 0;
	int bestMove = 0;
	for (int i = 1; i <= (SIZE * SIZE); i++) {
		State S = HB->getState();
		if (S.get_hex_colour(i) == State::BLANK) {
			S.set_hex_colour(i, State::COMPUTER);

			int currentResult = this->numberOfWins(S);
			if (currentResult > bestResult) {
				bestResult = currentResult;
				bestMove = i;
			}
		}
	}
	std::cout << "bestMove is:" << bestMove << endl;
	return bestMove;
}

/* Returns the result of number of games won. */
int MonteCarlo::numberOfWins(State &S) {

	int result = 0;
	for (int i = 0; i < NUMGAMES; i++) {
		srand(time(NULL));
		result += GameResult(S, State::COMPUTER);
	}
	return result;

}




int MonteCarlo::GameResult(State &S, State::Player player) {

	while(S.getMoves().size() != 0 ){

		vector<int> moves = S.getMoves();
		int moveRemoved = rand() % moves.size();
		int randomMove = moves[moveRemoved];

		//tests ****
		for(int i = 0 ; i < moves.size(); i++)
			cout << "moves[" << i << "] = " << moves[i] <<endl;
		cout << "removing n#" << moveRemoved << " (" << randomMove << ")" << endl;
		//test *****

		S.set_hex_colour(randomMove +1 , player); //+1 because (1,1) is actually 1
		S.removeMove(moveRemoved);

		//test ****
		for(int i = 0 ; i < moves.size(); i++)
					cout << "moves[" << i << "] = " << moves[i] <<endl;
		//test ****

		S.print();

		player = (player == State::HUMAN ? State::COMPUTER : State::HUMAN);

	}

	State::Player winner = HB->hasWon(S);
	if (winner == State::COMPUTER){
		return 1;
	}
	else if (winner == State::HUMAN){
		return 0;
	}

}

