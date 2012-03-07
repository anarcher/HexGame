/*
 * File:   HexGraph.h
 * Author: Pit Apps
 *
 * Created on 18 February 2012, 14:23
 */

#ifndef HEXGRAPH_H
#define	HEXGRAPH_H
#include "Graph.h"
#include "State.h"

class HexGraph : public Graph {
public:
    void dijkstra_run(int source, State::Player c, bool yesCol, State S);
private:
    PDeque make_queue(State::Player c, bool skip, State S);
};

#endif	/* HEXGRAPH_H */

