/**
 * Calculate Gershgorin bound
 *
 * Todo:
 *   1) check the process of getting value of Gershgorin bound is double as the
 *      diagonal element
 */
#ifndef VECTOR
#define VECTOR <vector>
#include VECTOR
#endif
#ifndef E_DENSE
#define E_DENSE <Eigen/Dense>
#include E_DENSE
#endif

double GershgorinBound(Eigen::MatrixXd & lap)
{
    double bound = 0;
    double curr_bound_val;


    for (int r=0; r<lap.rows(); ++r) {


        // clean the current bound value for next row
        curr_bound_val = 0;


        // get the sum of row of laplacian matrix for Gershgorin bound calculate
        for (int c=0; c<lap.cols(); ++c) {

            if (lap(r, c) < 0) {
                curr_bound_val -= lap(r, c);
            } else {
                curr_bound_val += lap(r, c);
            }
        }


        // compare with the bound
        if (bound < curr_bound_val) {
            bound = curr_bound_val;
        }
    }


    return bound;
}