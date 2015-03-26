/**
 * 
 */
#ifndef LOAD_GRAPH_H
#define LOAD_GRAPH_H

int mmRead(char *path, Eigen::MatrixXd & mat, int & numNodes);
int CreateGraph(Graph::Graph & g, Eigen::MatrixXd & adj_mat);

#endif