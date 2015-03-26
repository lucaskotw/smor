/**
 * Declare HDE function
 */
#ifndef HDE_H
#define HDE_H

#ifndef GRAPH
#define GRAPH "graph.hpp"
#include GRAPH
#endif

int ArgMax(Eigen::VectorXd & vec);
Eigen::MatrixXd HDE(Graph::Graph & g, int m);

#endif