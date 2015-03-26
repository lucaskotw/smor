/**
 * Returns the Laplacian matrix of the given graph
 * Laplacian Matrix is an appropriate Laplacian
 * Returns type: Eigen::MatrixXd
 */
#ifndef LAP
#define LAP
#ifndef GRAPH
#define GRAPH "graph.hpp"
#include GRAPH
#endif

Eigen::MatrixXd Laplacian(Graph::Graph g, double distPar);

#endif