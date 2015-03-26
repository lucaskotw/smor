/**
 * Declare subspace iteration
 */
#ifndef SUBSPACE_ITER
#define SUBSPACE_ITER

#ifndef E_DENSE
#define E_DENSE <Eigen/Dense>
#include E_DENSE
#endif
#ifndef G_BOUND
#define G_BOUND "g_bound.hpp"
#include G_BOUND
#endif
#ifndef ORTHO
#define ORTHO "ortho.hpp"
#include ORTHO
#endif


void SubspaceIteration(Eigen::MatrixXd & lap, Eigen::MatrixXd & basis);

#endif