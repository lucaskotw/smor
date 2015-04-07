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

Eigen::MatrixXd nonNormLaplacian(Graph::Graph & g);
/* Weighted Laplacian */
Eigen::MatrixXd wLaplacian(Graph::Graph & g, Eigen::MatrixXd & dist,
    double distPar);
/* Iterated Layout Laplacian Matrix */
Eigen::MatrixXd iterLayoutLaplacian(Graph::Graph & g, \
    Eigen::MatrixXd & dist, \
    Eigen::MatrixXd & coord, \
    double distPar);

#endif