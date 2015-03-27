/**
 * Implement Orthonormalize process
 */
#ifndef VECTOR
#define VECTOR <vector>
#include VECTOR
#endif
#ifndef E_DENSE
#define E_DENSE <Eigen/Dense>
#include E_DENSE
#endif
#ifndef IOSTREAM
#define IOSTREAM <iostream>
#include IOSTREAM
#endif


void Orthonormalize(Eigen::MatrixXd & basis)
{
    // show the result of orthonormal basis
    // std::cout << "Basis before orthornomalizing" << std::endl;
    // std::cout << "----------------------------" << std::endl;
    // std::cout << basis << std::endl;


    int nDim = basis.rows();
    double epsl = 0.001;
    Eigen::VectorXd center_vec(nDim);
    center_vec.fill(1);

    // normalize the vectors
    center_vec = center_vec / center_vec.norm();
    // std::cout << "center_vec" << std::endl;
    // std::cout << center_vec.transpose() << std::endl;
    

    double dotVal = 0;
    Eigen::VectorXd projVal(basis.rows());

    for (unsigned int i=0; i<basis.cols(); ++i) {

        // for each vector in basis, process with center_vec
        dotVal = basis.col(i).dot(center_vec);
        projVal = dotVal * center_vec;
        basis.col(i) = basis.col(i) - projVal;



        // process with previous vector after process with center_vec
        for (int j=0; j<i; ++j) {
            dotVal = basis.col(i).dot(basis.col(j));
            projVal = dotVal * basis.col(j);
            basis.col(i) = basis.col(i) - projVal;
        }

        // remove linearly dependent vectors
        if (basis.col(i).norm() < epsl) {

            basis.col(i).fill(0);



        } else {

            basis.col(i) = basis.col(i)/basis.col(i).norm();
        }
    }



    // show the result of orthonormal basis
    // std::cout << "Basis after orthornomalizing" << std::endl;
    // std::cout << "----------------------------" << std::endl;
    // std::cout << basis << std::endl;
    // std::cout << std::endl;
}