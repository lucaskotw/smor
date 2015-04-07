/**
 * Returns the Laplacian matrix of the given graph
 * Laplacian Matrix is an appropriate Laplacian
 * Returns type: Eigen::MatrixXd
 */
#ifndef GRAPH
#define GRAPH "graph.hpp"
#include GRAPH
#endif
#ifndef MATH
#define MATH
#include <math.h>
#endif


double invNorm(Eigen::MatrixXd & coord, int iR, int jR)
{
    Eigen::VectorXd diff(coord.cols());
    diff = (coord.row(iR) - coord.row(jR));
    return 1/diff.norm();
}



Eigen::MatrixXd nonNormLaplacian(Graph::Graph & g)
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


/* Return weighted laplacian matrix */
Eigen::MatrixXd wLaplacian(Graph::Graph & g, Eigen::MatrixXd & dist, \
    double distPar)
{
    int nNodes = g.getNumNodes();
    Eigen::MatrixXd lap(nNodes, nNodes);
    lap.fill(0);
    Eigen::VectorXd nbors;
    Eigen::VectorXd distRow;
    for (int i=0; i<g.getNumNodes(); ++i) {

        // if node j is node i's neighbor
        nbors.resize(g.adj(i).size());
        nbors = g.adj(i);
        distRow.resize(g.getNumNodes());
        distRow = dist.row(i);
        lap.row(i) = -1 * distRow.array().pow(-1 * distPar);

        lap(i, i) = 0;
        for (int j=0; j<distRow.size(); ++j) {
            if (i != j) {
                lap(i, i) += pow(distRow(j), -1 * distPar);
            }
        }

    }

    return lap;
}


/* Return iterated layout laplacian matrix */
Eigen::MatrixXd iterLayoutLaplacian(Graph::Graph & g, \
    Eigen::MatrixXd & dist, \
    Eigen::MatrixXd & coord, \
    double distPar)
{
    int nNodes = g.getNumNodes();
    Eigen::MatrixXd lap(nNodes, nNodes);
    lap.fill(0);
    Eigen::VectorXd nbors;
    Eigen::VectorXd distRow(nNodes);
    for (int i=0; i<g.getNumNodes(); ++i) {

        // if node j is node i's neighbor
        nbors.resize(g.adj(i).size());
        nbors = g.adj(i);
        distRow.resize(g.getNumNodes());
        distRow = dist.row(i);
        // distRow
        // std::cout << "distRow" << std::endl;
        // std::cout << distRow << std::endl;
        for (int j=0; j<distRow.size(); ++j) {
            if (i != j) {
                lap(i, j) = std::pow(distRow(j), -1 * distPar); // w_{ij} = d_{ij}^-2
                lap(i, j) = -1 * lap(i, j) * distRow(j) * invNorm(coord, i, j);
                // lap(i, j) = invNorm(coord, i, j);
                lap(i, i) -= lap(i, j); // added to diagonal
            }
        }
    }

    return lap;
}