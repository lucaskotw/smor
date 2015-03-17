/**
 * Returns the Laplacian matrix of the given graph
 * Returns type: std::vector< std::vector<int> >
 */
#ifndef MATRIXOP
#define MATRIXOP "matrix_op.h"
#include MATRIXOP
#endif
#ifndef GRAPH
#define GRAPH "graph.h"
#include GRAPH
#endif


std::vector< std::vector<double> > Laplacian(Graph::Graph g)
{
    int nNodes = g.getNumNodes();
    std::vector< std::vector<double> > lap(nNodes, std::vector<double>(nNodes, 0));
    for (int i=0; i<g.getNumNodes(); ++i) {

        // if node j is node i's neighbor
        std::vector<int> nbors = g.adj(i);
        for (int j=0; j<nbors.size(); ++j) {
            lap[i][nbors.at(j)] = -1;
        }

        // node i self value (diagonal)
        lap[i][i] = (double)g.deg(i);
    }


    // show the result of laplacian matrix
    // std::cout << "Laplacian Matrix" << std::endl;
    // std::cout << "----------------" << std::endl;
    // printMat(lap);

    return lap;
}