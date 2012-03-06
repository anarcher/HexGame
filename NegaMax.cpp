/* 
 * File:   NegaMax.cpp
 * Author: Koy
 * 
 * Created on 06 March 2012, 14:18
 */

#include "NegaMax.h"
#include <algorithm>
using namespace std;

pair<double, int> NegaMax::nm_compute(HexBoard board, int currentDepth, double alpha, double beta) {
    if (board.isFinished() || currentDepth <= 0) {
        //  return make_pair(eval(),0); //TODO return eval function result.
    }

    int bestMove = 0;
    double bestScore = NEGINF;

    vector<int> moves = board.getMoves();
    for (vector<int>::iterator i = moves.begin(); i != moves.end(); i++) {
        HexBoard newBoard = board.makemove(*i);

        pair<double, int> result = nm_compute(newBoard, currentDepth - 1, -beta, -(max(alpha, bestScore)));
        double currentScore = -(result.first);

        if (currentScore > bestScore) {
            bestScore = currentScore;
            bestMove = *i;

            // AB-Pruning
            if (bestScore >= beta) {
                return make_pair(bestScore, bestMove);
            }
        }
    }
    return make_pair(bestScore, bestMove);
}

int NegaMax::getBestMove(HexBoard board, int maxDepth) {
    pair<double, int> move = nm_compute(board, maxDepth, NEGINF, INF);
    return move.second;
}
