/**
 * Perform Orthonormalize process
 */
#ifndef ORTHO
#define ORTHO

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


void Orthonormalize(Eigen::MatrixXd & basis);

#endif