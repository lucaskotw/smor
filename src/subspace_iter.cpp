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

/* Use to remove the column */
void removeColumn(Eigen::MatrixXd& matrix, unsigned int colToRemove)
{
    unsigned int numRows = matrix.rows();
    unsigned int numCols = matrix.cols()-1;

    if( colToRemove < numCols )
        matrix.block(0,colToRemove,numRows,numCols-colToRemove) = matrix.block(0,colToRemove+1,numRows,numCols-colToRemove);

    matrix.conservativeResize(numRows,numCols);
    std::cout << "current matrix" << std::endl;
    std::cout << matrix << std::endl;
}


void SubspaceIteration(Eigen::MatrixXd & lap, \
                       Eigen::MatrixXd & basis)
{
    const int iteration=100;
    // Compute Gershgorin bound
    double bound = GershgorinBound(lap);
    std::cout << "g_bound = " << bound << std::endl;
    Orthonormalize(basis);


    // process
    int subDim;
    Eigen::MatrixXd unit(basis.cols(), basis.cols());
    unit.fill(1);
    Eigen::MatrixXd gI = bound * unit;
    Eigen::MatrixXd gPart = gI - lap;

    for (int i=0; i<iteration; ++i) {
        subDim = basis.cols();

        for (int j=0; j<subDim; ++j) {

            basis.col(j) = gPart * basis.col(j);

        }

        if (i % 3 == 0) {
            Orthonormalize(basis);
        }
    }


    for (unsigned int cc=0; cc<basis.cols(); ++cc)
    {
        if (basis.col(cc).norm() == 0) removeColumn(basis, cc);
    }

    std::cout << "current basis" << std::endl;
    std::cout << basis << std::endl;

}