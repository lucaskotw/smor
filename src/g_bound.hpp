/**
 * Declare Gershgorin bound
 *
 * Todo:
 *   1) check the process of getting value of Gershgorin bound is double as the
 *      diagonal element
 */
#ifndef G_BOUND
#define G_BOUND

#ifndef VECTOR
#define VECTOR <vector>
#include VECTOR
#endif
#ifndef E_DENSE
#define E_DENSE <Eigen/Dense>
#include E_DENSE
#endif

double GershgorinBound(Eigen::MatrixXd & lap);

#endif