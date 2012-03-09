/*
 * MonteCarlo.h
 *
 *  Created on: Mar 8, 2012
 *      Author: jonathanbibas
 */

#ifndef MONTECARLO_H_
#define MONTECARLO_H_
#include "HexBoard.h"
static const double NEGINF = -INF;


class MonteCarlo {
public:
    MonteCarlo();
    ~MonteCarlo();
    int getBestMove(HexBoard &board, State::Player player);
    bool GameResult(State state, int currentMove, State::Player player);
    int numberOfWins(State state, int firstmove);
private:

};


#endif /* MONTECARLO_H_ */
