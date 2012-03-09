/*
 * File:   HexGraph.cpp
 * Author: Pit Apps
 *
 * Created on 18 February 2012, 14:23
 */

#include "HexGraph.h"
using namespace std;

/* Modified Dijkstra which takes colour into account.
 * yesCol true means only paths for this colour are taken into account; false means only paths not including this colour  */
void HexGraph::dijkstra_run(int source, State::Player c, State S) {
    set_all_vertex();
    set_vertex(source, 0, NIL);
    PDeque Q = make_queue(c, S);

    make_heap(Q.begin(), Q.end(), Pcomp());

    while (!Q.empty()) {
        int x = Q.front().second;
        Q.pop_front();
        for (Graph::EdList::iterator j = adj[x].begin(); j != adj[x].end(); ++j) {
            double newDist = get_dist(x) + j->weight;
            if (get_dist(j->dest) > newDist) {
                State::Player col = S.get_hex_colour(j->dest);
                if (col == c) {
                    set_vertex(j->dest, newDist, x);
                    make_heap(Q.begin(), Q.end(), Pcomp());
                }
            }
        }
    }
}

/* Overloaded function which makes a queue of distance->destination edge pairs.
 * It skips any colours mentioned in the parameters if skip is true; else it 
 * only adds edges of colour c.
 */
PDeque HexGraph::make_queue(State::Player c, State S) {
    PDeque Q;
    for (AdjMap::iterator i = adj.begin(); i != adj.end(); ++i) {
        State::Player col = S.get_hex_colour(i->first);
        if (col == c) {
            Q.push_back(make_pair(&(prop[i->first].dist), i->first));
        }
    }
    return Q;
}