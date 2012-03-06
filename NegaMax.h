/* 
 * File:   NegaMax.h
 * Author: Koy
 *
 * Created on 06 March 2012, 14:18
 */

#ifndef NEGAMAX_H
#define	NEGAMAX_H
#include "HexBoard.h"

static const double NEGINF = -INF;

class NegaMax {
public:
    NegaMax();
    std::pair<double,int> nm_compute(HexBoard board, int currentDepth, double alpha, double beta);
    int getBestMove(HexBoard board, int maxDepth);
private:

};

#endif	/* NEGAMAX_H */

