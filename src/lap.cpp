/**
 * Returns the Laplacian matrix of the given graph
 * Laplacian Matrix is an appropriate Laplacian
 * Returns type: Eigen::MatrixXd
 */
#ifndef GRAPH
#define GRAPH "graph.hpp"
#include GRAPH
#endif



Eigen::MatrixXd nonNormLaplacian(Graph::Graph g)
{
    int nNodes = g.getNumNodes();
    Eigen::MatrixXd lap(nNodes, nNodes);
    lap.fill(0);
    Eigen::VectorXd nbors;
    for (int i=0; i<g.getNumNodes(); ++i) {

        // if node j is node i's neighbor
        nbors.resize(g.adj(i).size());
        nbors = g.adj(i);
        for (int j=0; j<nbors.size(); ++j)
        {
            lap(i, nbors(j)) = -1;
        }

        lap(i, i) = nbors.size();

    }

    return lap;
}


Eigen::MatrixXd Laplacian(Graph::Graph g, double distPar)
{
    int nNodes = g.getNumNodes();
    Eigen::MatrixXd lap(nNodes, nNodes);
    lap.fill(0);
    Eigen::VectorXd nbors;
    Eigen::VectorXd dist;
    for (int i=0; i<g.getNumNodes(); ++i) {

        // if node j is node i's neighbor
        nbors.resize(g.adj(i).size());
        nbors = g.adj(i);
        dist.resize(g.getNumNodes());
        dist = g.BFS(i);
        lap.row(i) = -1 * dist.array().pow(-1 * distPar);

        lap(i, i) = 0;
        for (int j=0; j<dist.size(); ++j) {
            if (i != j) {
                lap(i, i) += pow(dist(j), -1 * distPar);
            }
        }

    }

    return lap;
}