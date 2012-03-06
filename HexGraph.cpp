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
void HexGraph::dijkstra_run(int source, HexCol c, bool yesCol) {
    set_all_vertex();
    set_vertex(source, 0, NIL);
    PDeque Q;

    Q = make_queue(c, !yesCol);

    make_heap(Q.begin(), Q.end(), Pcomp());

    while (!Q.empty()) {
        int x = Q.front().second;
        Q.pop_front();
        for (Graph::EdList::iterator j = adj[x].begin(); j != adj[x].end(); ++j) {
            double newDist = get_dist(x) + j->weight;
            if (get_dist(j->dest) > newDist) {
                if ((yesCol && get_hex_colour(j->dest) == c) || (!yesCol && get_hex_colour(j->dest) != c)) {
                    set_vertex(j->dest, newDist, x);
                    make_heap(Q.begin(), Q.end(), Pcomp());
                }
            }
        }
    }
}

/* Sets the colour of a given vertex. */
void HexGraph::set_hex_colour(int vertex, HexCol c) {
    propC[vertex].colour = c;
}

/* Gets the colour of a given vertex. */
HexGraph::HexCol HexGraph::get_hex_colour(int vertex) {
    return propC[vertex].colour;
}

/* Optimizes the weights around a placed piece. */
void HexGraph::optimise_weight(int vertex) {
    HexCol c = propC[vertex].colour;
    for (EdList::iterator i = adj[vertex].begin(); i != adj[vertex].end(); ++i) {
        if (propC[i->dest].colour == c) {
            i->weight = 0;
        } else {
            i->weight = 0.5;
        }
    }
}

/* Resets weight values for the graph. */
void HexGraph::reset_weight() {
    for (AdjMap::iterator i = adj.begin(); i != adj.end(); ++i) {
        for (EdList::iterator j = i->second.begin(); j != i->second.end(); ++j) {
            j->weight = 1;
        }
    }
}

/* Overloaded function which makes a queue of distance->destination edge pairs.
 * It skips any colours mentioned in the parameters if skip is true; else it 
 * only adds edges of colour c.
 */
PDeque HexGraph::make_queue(HexCol c, bool skip) {
    PDeque Q;
    for (AdjMap::iterator i = adj.begin(); i != adj.end(); ++i) {
        HexCol col = get_hex_colour(i->first);
        if ((skip && col != c) || (!skip && col == c)) {
            Q.push_back(make_pair(&(prop[i->first].dist), i->first));
        }
    }
    return Q;
}