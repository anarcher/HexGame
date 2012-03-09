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

class State {
public:

    State() : turns(0) {
    };

    enum Player {
        BLANK = 0, COMPUTER = 1, HUMAN = 2
    };
    typedef std::map<int, Player> PieceMap;

    Player get_hex_colour(int vertex);
    void set_hex_colour(int vertex, Player c);

    void setTurns(int turns);
    int getTurns();
    
    std::vector<int> getMoves();

private:
    int turns;
    PieceMap piece;
};

#endif	/* STATE_H */

