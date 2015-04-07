/**
 * 
 */
#ifndef LOAD_GRAPH_H
#define LOAD_GRAPH_H


void getEdgesFromInput(char * str, int charSize, \
    int & rElem, int & cElem, double & val);
int mmRead(char *path, Eigen::MatrixXd & mat, int & numNodes);
int CreateGraph(Graph::Graph & g, Eigen::MatrixXd & adj_mat);

#endif