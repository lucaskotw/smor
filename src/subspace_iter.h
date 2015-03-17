/**
 * Perform subspace iteration
 */
#ifndef MATRIXOP
#define MATRIXOP "matrix_op.h"
#include MATRIXOP
#endif
#ifndef GERSHGORIN
#define GERSHGORIN "gershgorin_bound.h"
#include GERSHGORIN
#endif
#ifndef ORTHO
#define ORTHO "orthonormalize.h"
#include ORTHO
#endif


void SubspaceIteration(std::vector< std::vector<double> > & lap, \
                       std::vector< std::vector<double> > & basis)
{
    const int iteration=5;
    // Compute Gershgorin bound
    double bound = GershgorinBound(lap);
    Orthonormalize(basis);


    // process
    int subDim = basis.size();
    std::vector< std::vector<double> > unit = unitMat(basis[0].size());
    std::vector< std::vector<double> > gI = MatScalarMultiply(bound, unit);
    std::vector< std::vector<double> > gPart = MatSubtract(gI, lap);
    std::vector<double> updatedBasis;

    for (int i=0; i<iteration; ++i) {

        for (int j=0; j<subDim; ++j) {
            updatedBasis.clear();
            updatedBasis = MatVecMultiply(gPart, basis.at(j));
            basis[j] = updatedBasis;
            // std::cout << "updated basis" << std::endl;
            // printVec(updatedBasis);    
        }
        // std::cout << "iteration #" << i << std::endl;
        
        // std::cout << "basis size: " << basis.size() << std::endl;
        // printMat(basis);
        // std::cout << "end updating basis in this iteration" << std::endl;
        if (i % 3 == 0) {
            Orthonormalize(basis);
        }
    }


}