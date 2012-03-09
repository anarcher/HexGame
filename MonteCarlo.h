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
static const int NUMGAMES = 20000;

class MonteCarlo {
public:

    MonteCarlo(HexBoard *HB) : HB(HB) {
    };
    int getBestMove();
private:
    int GameResult(State &S, State::Player player);
    int numberOfWins(State &S);
    HexBoard *HB;
};


#endif /* MONTECARLO_H_ */
