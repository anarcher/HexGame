/*
 * File:   HexGraph.h
 * Author: Pit Apps
 *
 * Created on 18 February 2012, 14:23
 */

#ifndef HEXGRAPH_H
#define	HEXGRAPH_H
#include "Graph.h"

class HexGraph : public Graph {
public:

    enum HexCol {
        BLANK = 0, COMPUTER = 1, HUMAN = 2
    };

    HexCol get_hex_colour(int vertex);
    void set_hex_colour(int vertex, HexCol c);
    void optimise_weight(int vertex);
    void reset_weight();

    void dijkstra_run(int source, HexCol c, bool yesCol);
    PDeque make_queue(HexCol c);
private:

    typedef struct propo {
        HexCol colour;
    } property;

    typedef std::map<int, property> PropMap;
    PropMap propC;
};

#endif	/* HEXGRAPH_H */

