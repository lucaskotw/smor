/**
 * Run all-pair shortest path through iterate the whole graph
 * via BFS to each vertex
 */
#ifndef GRAPH
#define GRAPH "graph.h"
#include GRAPH
#endif


Eigen::MatrixXd allPairShortestPath(Graph::Graph & g)
{
    Eigen::MatrixXd dist(g.getNumNodes(), g.getNumNodes());
    dist.fill(0);
    for (int i=0; i<g.getNumNodes(); ++i) {
        dist.row(i) = g.BFS(i);
    }

    return dist;
}