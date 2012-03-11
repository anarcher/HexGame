/* 
 * File:   State.h
 * Author: Pit Apps
 *
 * Created on 06 March 2012, 19:52
 */

#ifndef STATE_H
#define	STATE_H
#include <map>
#include <vector>
#include <iostream>

class State {
public:

    State() : turns(0) {
        piece.resize(122);
    };

    enum Player {
        BLANK = 0, COMPUTER = 1, HUMAN = 2
    };

    Player get_hex_colour(int vertex);
    void set_hex_colour(int vertex, Player c);

    void setTurns(int turns);
    int getTurns();

    void print();

    std::vector<int> getMoves();
    void removeMove(int i);
    void fillMoves();
    int getSize();

    int getNextMove();

private:
    int turns;
    std::vector<Player> piece;
    std::vector<int> moves;
};

#endif	/* STATE_H */

