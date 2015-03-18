/**
 * Implement 2D stress subspace process
 */
#ifndef GRAPH
#define GRAPH "graph.h"
#include GRAPH
#endif
#ifndef VECTOR
#define VECTOR <vector>
#include VECTOR
#endif
#ifndef LAPLACIAN
#define LAPLACIAN "laplacian.h"
#include LAPLACIAN
#endif


/***************
    Absolute
****************/
double abs(double a) {
    if (a < 0) {
        return -a;
    } else {
        return a;
    }
}



/***************
    Norm-1
****************/
double norm1(double a, double b)
{
    double result = a - b;
    return abs(result);
}



/**********************************************************
    Stress Major Process, Modify given x, y coordinates
***********************************************************/
std::vector< std::vector<double> > getResidualDist( \
    std::vector< std::vector<double> > & lap \
    std::vector<double> & refCoord)
{
    std::vector< std::vector<double> > dist (lap.size(), \
        std::vector<double> (lap.size(), 0));
    double normVal;
    for (int i=0; i<lap.size(); ++i) {
        for (int j=0; j<lap.size(); ++j) {
            normVal = norm1(refCoord[i] - refCoord[j]);
            if (lap[i][j] > normVal) {
                dist[i][j] = sqrt( (lap[i][j])^2 - normVal^2 );
            }
        }
    }


    return dist;
}


/**********************************************************
    Stress Major Process, Modify given x, y coordinates
***********************************************************/
std::vector<double> computeNextSol(std::vector< std::vector<double> > & lap, \
    std::vector<double> & tilCoord, std::vector<double> & refCoord, \
    double distPar)
{

    // initial solution vector
    std::vector<double> sol;
    double elemSum; // solution element's initialization

    // calculate residual distance
    std::vector< std::vector<double> > resi_dist = getResidualDist(lap, refCoord);


    // calculate next solution of the linear system
    for (int i=0; i<resi_dist.size(); ++i) {
        elemSum = 0;
        for (int j=0; j<resi_dist.size(); ++j) {
            if ((lap[i][j] != 0) & (i!=j)) {
                if (tilCoord[i] >= tilCoord[j]) {
                    elemSum += pow(resi_dist[i][j], 1-distPar);
                } else {
                    elemSum -= pow(resi_dist[i][j], 1-distPar);
                }
            }
        }
        sol = elemSum;

    }



}



std::vector<double> computeNextLayoutVec(A, basis, xTil, b_x);



/**********************************************************
    Stress Major Process, Modify given x, y coordinates
***********************************************************/
void twoDimStressSubspace(Graph::Graph & g, \
                          std::vector< std::vector<double> > & basis, \
                          std::vector<double> & x_coord, \
                          std::vector<double> & y_coord)
{
    std::vector< std::vector<double> > lap = Laplacian(g);
    std::vector< std::vector<double> > A = QuadMultiply(basis, lap);

    std::vector<double> xTil;
    std::vector<double> yTil;
    std::vector<double> b_x;
    std::vector<double> b_y;
    std::vector<double> v;

    while ((xTil != x) || (yTil != y)) {

        // improve the x-axis
        xTil = x_coord;
        b_x = computeNextSol(lap, xTil, y_coord, 2); // distPar (alpha) = 2
        v = computeNextLayoutVec(A, basis, xTil, b_x);
        x_coord = MatVecMultiply(basis, v);



        // improve the y-axis
        yTil = y_coord;
        b_y = computeNextSol(lap, yTil, x_coord, 2); // distPar (alpha) = 2
        v = computeNextLayoutVec(A, basis, b_x);
        y_coord = MatVecMultiply(basis, v);
    }
}