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

double diffclock(clock_t clock1, clock_t clock2) {
    double diffticks = clock1 - clock2;
    double diffms = (diffticks * 1000) / CLOCKS_PER_SEC;
    return diffms;
}

int MonteCarlo::getBestMove() {

    int bestResult = 0;
    int bestMove = 0;
    clock_t begin = clock();
    srand(time(NULL));

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
        //cout << "ai games played for candidate-move " << i << "..." << endl;
    }
    clock_t end = clock();

    cout << "Time elapsed: " << double(diffclock(end, begin)) << " ms" << endl;
    std::cout << "bestMove is:" << bestMove << endl;
    return bestMove;
}

/* Returns the result of number of games won. */
int MonteCarlo::numberOfWins(State &S) {

    int result = 0;
    for (int i = 0; i < NUMGAMES; i++) {
        result += GameResult(S, State::COMPUTER);
    }
    return result;

}

int MonteCarlo::GameResult(State S, State::Player player) {

    S.fillMoves();
    S.shuffleMoves();

    while (!S.movesEmpty()) {
        int randomMove = S.getNextMove();
        S.set_hex_colour(randomMove, player);
        player = (player == State::HUMAN ? State::COMPUTER : State::HUMAN);
    }

    State::Player winner = HB->hasWon(S);

    if (winner == State::COMPUTER) {
        return 1;
    } else if (winner == State::HUMAN) {
        return 0;
    }

}

