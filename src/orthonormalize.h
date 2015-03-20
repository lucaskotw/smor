/**
 * Perform Orthonormalize process
 */
#ifndef VECTOR
#define VECTOR <vector>
#include VECTOR
#endif
#ifndef E_DENSE
#define E_DENSE <Eigen/Dense>
#include E_DENSE
#endif
#ifndef VECTOROP
#define VECTOROP "vector_op.h"
#include VECTOROP
#endif
#ifndef IOSTREAM
#define IOSTREAM <iostream>
#include IOSTREAM
#endif


void Orthonormalize(Eigen::MatrixXd & basis)
{
    int nDim = basis.cols();
    double epsl = 0.001;
    Eigen::VectorXd center_vec(nDim);
    center_vec.fill(1);

    // normalize the vectors
    center_vec = center_vec / center_vec.norm();
    

    double dotVal = 0;
    Eigen::VectorXd projVal(basis.cols());

    for (int i=0; i<basis.rows(); ++i) {

        // for each vector in basis, process with center_vec
        dotVal = basis.row(i).dot(center_vec);
        projVal = dotVal * center_vec;
        basis.row(i) = basis.row(i) - projVal.transpose();



        // process with previous vector after process with center_vec
        for (int j=0; j<i; ++j) {
            dotVal = basis.row(i).dot(basis.row(j));
            projVal = dotVal * basis.row(j);
            basis.row(i) = basis.row(i) - projVal.transpose();
        }

        // remove linearly dependent vectors
        if (basis.row(i).norm() < epsl) {

            basis.row(i).fill(0);


        } else {

            basis.row(i) = basis.row(i)/basis.row(i).norm();
        }
    }


    // show the result of orthonormal basis
    std::cout << "Basis after orthornomalizing" << std::endl;
    std::cout << "----------------------------" << std::endl;
    std::cout << basis << std::endl;
    std::cout << std::endl;
}