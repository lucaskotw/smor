/**
 * Run all-pair shortest path through iterate the whole graph
 * via BFS to each vertex
 */
#ifndef ALL_PAIR
#define ALL_PAIR

#ifndef GRAPH
#define GRAPH "graph.hpp"
#include GRAPH
#endif

Eigen::MatrixXd allPairShortestPath(Graph::Graph & g);

#endif