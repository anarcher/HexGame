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

		cout << "al games played for candidate-move " << i << "..." << endl;
		/*	FEEDBACK FOR WAITING
		 switch (i){
		case (SIZE * SIZE)/10:
		cout << "Please wait 10..." <<endl;
		case (SIZE * SIZE)/9:
		cout << "9..." <<endl;
		break;
		case (SIZE * SIZE)/8:
		cout << "8..." <<endl;
		break;
		case (SIZE * SIZE)/7:
		cout << "7..." <<endl;
		break;
		case (SIZE * SIZE)/6:
		cout << "6..." <<endl;
		break;
		case (SIZE * SIZE)/5:
		cout << "5..." <<endl;
		break;
		case (SIZE * SIZE)/4:
		cout << "4..." <<endl;
		break;
		case (SIZE * SIZE)/3:
		cout << "3..." <<endl;
		break;
		case (SIZE * SIZE)/2:
		cout << "2..." <<endl;
		break;
		case (SIZE * SIZE)/1:
		cout << "1..." <<endl;
		break;
		}
		*/

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
		//cout << "game " << i << "..." << endl;



	}
	return result;

}




int MonteCarlo::GameResult(State S, State::Player player) {

	//S.print();

	S.fillMoves();

	//cout << "moves filled (size = " << S.getMoves().size() << ")" << endl;

	while(S.getSize() > 0 ){

		int moveRemoved = rand() % S.getSize();
		int randomMove = S.getMoves()[moveRemoved];

		//cout << "the random: " << moveRemoved << "(" << randomMove << ")"  <<endl;
		/* tests ****
		for(int i = 0 ; i < S.getSize(); i++)
			cout << "moves[" << i << "] = " << S.getMoves()[moveRemoved] <<endl;
		cout << "removing n#" << moveRemoved << " (" << randomMove << ")" << endl;
		test *****/

		S.set_hex_colour(randomMove +1 , player); //+1 because (1,1) is actually 1
		S.removeMove(moveRemoved);


		//S.print();

		player = (player == State::HUMAN ? State::COMPUTER : State::HUMAN);

	}
	//cout << "GAME FINISHED\n\n\n" << endl;
	State::Player winner = HB->hasWon(S);
	if (winner == State::COMPUTER){
		return 1;
	}
	else if (winner == State::HUMAN){
		return 0;
	}

}

