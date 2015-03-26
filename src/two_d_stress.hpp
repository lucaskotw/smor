/**
 * Implement 2D stress subspace process
 */
#ifndef TWO_D_STRESS
#define TWO_D_STRESS
#ifndef GRAPH
#define GRAPH "graph.hpp"
#include GRAPH
#endif
#ifndef E_DENSE
#define E_DENSE <Eigen/Dense>
#include E_DENSE
#endif
#ifndef VECTOR
#define VECTOR <vector>
#include VECTOR
#endif
#ifndef LAP
#define LAP "lap.hpp"
#include LAP
#endif


double abs(double a);
double norm1(double a, double b);

Eigen::MatrixXd getResidualDist( \
    Eigen::MatrixXd & dist, \
    Eigen::VectorXd & refCoord);
Eigen::VectorXd computeNextSol(Eigen::MatrixXd & lap, \
    Eigen::MatrixXd & dist, \
    Eigen::VectorXd & tilCoord, Eigen::VectorXd & refCoord, \
    double distPar);
Eigen::VectorXd computeNextLayoutVec(Eigen::MatrixXd & A, \
    Eigen::MatrixXd & basis, \
    Eigen::VectorXd & xTil, \
    Eigen::VectorXd & b_x);

void twoDimStressSubspace(Graph::Graph & g, \
                          Eigen::MatrixXd & lap, \
                          Eigen::MatrixXd & dist, \
                          Eigen::MatrixXd & basis, \
                          Eigen::VectorXd & x_coord, \
                          Eigen::VectorXd & y_coord);

#endif