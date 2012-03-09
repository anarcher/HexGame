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

    double bestResult = NEGINF;
    int bestMove = 0;
    for (int i = 1; i < SIZE * SIZE; i++) {
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
    return bestMove;
}

int MonteCarlo::GameResult(State &S, State::Player player) {

    State::Player winner = HB->hasWon(S);
    switch (winner) {
        case State::COMPUTER:
            return 0;
        case State::HUMAN:
            return 1;
        default:
            break;
    }

    srand(time(NULL));
    int randomMove = rand() % (SIZE * SIZE);

    while (S.get_hex_colour(randomMove) != State::BLANK) {
        randomMove = rand() % (SIZE * SIZE);
    }

    S.set_hex_colour(randomMove, player);

    player = (player == State::HUMAN ? State::COMPUTER : State::HUMAN);

    GameResult(S, player);
}

/* Returns the result of number of games won. */
int MonteCarlo::numberOfWins(State &S) {

    int result = 0;
    for (int i = 0; i < NUMGAMES; i++) {
        result += GameResult(S, State::COMPUTER);
    }
    return result;
}
