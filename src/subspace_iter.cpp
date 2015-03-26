/**
 * Implement subspace iteration
 */
#ifndef E_DENSE
#define E_DENSE <Eigen/Dense>
#include E_DENSE
#endif
#ifndef GERSHGORIN
#define GERSHGORIN "g_bound.hpp"
#include GERSHGORIN
#endif

#include "ortho.hpp"


void SubspaceIteration(Eigen::MatrixXd & lap, \
                       Eigen::MatrixXd & basis)
{
    const int iteration=100;
    // Compute Gershgorin bound
    double bound = GershgorinBound(lap);
    Orthonormalize(basis);


    // process
    int subDim = basis.rows();
    Eigen::MatrixXd unit(basis.cols(), basis.cols());
    unit.fill(1);
    Eigen::MatrixXd gI = bound * unit;
    Eigen::MatrixXd gPart = gI - lap;

    for (int i=0; i<iteration; ++i) {

        for (int j=0; j<subDim; ++j) {

            basis.row(j) = gPart * basis.row(j).transpose();

        }

        if (i % 3 == 0) {
            Orthonormalize(basis);
        }
    }


}