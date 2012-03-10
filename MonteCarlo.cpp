/*
 * File:   MonteCarlo.cpp
 * Author: Jonathan Bibas
 *
 * Created on 06 March 2012, 14:18
 */

#include "MonteCarlo.h"
#include <ctime>
#include <cstdlib>
#include <algorithm>
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

int MonteCarlo::GameResult(State S, State::Player player) {

    S.fillMoves();
    vector<int> moves = S.getMoves();
    random_shuffle(moves.begin(), moves.end());

    while (S.getSize() > 0) {

        int randomMove = S.getNextMove();
        S.set_hex_colour(randomMove, player); //+1 because (1,1) is actually 1
        player = (player == State::HUMAN ? State::COMPUTER : State::HUMAN);

    }

    State::Player winner = HB->hasWon(S);

    if (winner == State::COMPUTER) {
        return 1;
    } else if (winner == State::HUMAN) {
        return 0;
    }

}

