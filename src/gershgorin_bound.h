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

double GershgorinBound(std::vector< std::vector<double> > & lap)
{
    double bound = 0;
    double curr_bound_val;


    for (std::vector< std::vector<double> >::iterator itRR=lap.begin(); \
         itRR!=lap.end(); \
         ++itRR) {


        // clean the current bound value for next row
        curr_bound_val = 0;


        // get the sum of row of laplacian matrix for Gershgorin bound calculate
        for (std::vector<double>::iterator itCC=(*itRR).begin(); \
                 itCC!=(*itRR).end(); \
                 ++itCC) {

            if (*itCC < 0) {
                curr_bound_val -= *itCC;
            } else {
                curr_bound_val += *itCC;
            }
        }


        // compare with the bound
        if (bound < curr_bound_val) {
            bound = curr_bound_val;
        }
    }


    return bound;
}