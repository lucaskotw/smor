/**
 * Implement 2D stress subspace process
 */
#ifndef GRAPH
#define GRAPH "graph.hpp"
#include GRAPH
#endif
#ifndef E_DENSE
#define E_DENSE <Eigen/Dense>
#include E_DENSE
#endif
#ifndef VECTOR
#define VECTOR <vector>
#include VECTOR
#endif
#ifndef LAP
#define LAP "lap.hpp"
#include LAP
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
Eigen::MatrixXd getResidualDist( \
    Eigen::MatrixXd & dist, \
    Eigen::VectorXd & refCoord)
{
    Eigen::MatrixXd resi_dist(dist.rows(), dist.cols());
    resi_dist.fill(0);
    double normVal;
    for (int i=0; i<dist.rows(); ++i) {
        for (int j=0; j<dist.cols(); ++j) {
            normVal = norm1(refCoord(i), refCoord(j));
            if (dist(i, j) > normVal) {
                resi_dist(i, j) = sqrt( pow(dist(i, j), 2) - dist(normVal, 2) );
            }
        }
    }

    // std::cout << "result distance:" << std::endl;
    // std::cout << resi_dist << std::endl;

    return resi_dist;
}


/*********************************************************
    Stress Major Process, Modify given x, y coordinates
**********************************************************/
Eigen::VectorXd computeNextSol(Eigen::MatrixXd & lap, \
    Eigen::MatrixXd & dist, \
    Eigen::VectorXd & tilCoord, Eigen::VectorXd & refCoord, \
    double distPar)
{

    // initial solution vector
    Eigen::VectorXd sol(dist.rows());
    double elemSum; // solution element's initialization

    // calculate residual distance
    Eigen::MatrixXd resi_dist = getResidualDist(dist, refCoord);


    // calculate next solution of the linear system
    for (int i=0; i<resi_dist.rows(); ++i) {
        elemSum = 0;
        for (int j=0; j<resi_dist.cols(); ++j) {
            if ( (dist(i, j) != 0) & (i != j) ) {
                if (tilCoord(i) >= tilCoord(j)) {
                    elemSum += resi_dist(i, j) * pow(dist(i, j), -distPar);
                } else {
                    elemSum -= resi_dist(i, j) * pow(dist(i, j), -distPar);
                }
            }
        }
        sol(i) = elemSum;

    }


    return sol;

}


/**************************************************************
    compute the next layout vector for coordinates adjustment
    assume A is dense
 **************************************************************/
Eigen::VectorXd computeNextLayoutVec(Eigen::MatrixXd & A, \
    Eigen::MatrixXd & basis, \
    Eigen::VectorXd & xTil, \
    Eigen::VectorXd & b_x)
{
    Eigen::VectorXd sol(basis.rows());
    sol = (A.transpose() * A).ldlt().solve(A.transpose() * basis * b_x);

    return sol;
}




/**********************************************************
    Stress Major Process, Modify given x, y coordinates
***********************************************************/
// x and y coordinates are the first and second row of basis
// and pass in the calculated basis
void twoDimStressSubspace(Graph::Graph & g, \
                          Eigen::MatrixXd & lap, \
                          Eigen::MatrixXd & dist, \
                          Eigen::MatrixXd & basis, \
                          Eigen::VectorXd & x_coord, \
                          Eigen::VectorXd & y_coord)
{

    // Eigen::MatrixXd lap = Laplacian(g);
    // std::cout << "current basis" << std::endl;
    // std::cout << basis << std::endl;

    Eigen::MatrixXd A = basis * lap * basis.transpose();

    // std::cout << "A matrix" << std::endl;
    // std::cout << A << std::endl;


    Eigen::VectorXd xTil;
    Eigen::VectorXd yTil;
    Eigen::VectorXd b_x;
    Eigen::VectorXd b_y;
    Eigen::VectorXd v;

    int i = 0;
    // while ((xTil != x_coord) || (yTil != y_coord)) {
    int ter = 0; // clean: after check the error of the code
    // while(true) {
    while(ter<200) {
    // for (int i=0; i<11; ++i) {
        // improve the x-axis
        xTil = x_coord;
        b_x = computeNextSol(lap, dist, xTil, y_coord, 2); // distPar (alpha) = 2
        // std::cout << "next x layout solution" << std::endl;
        // std::cout << "b_x = " << b_x.transpose() << std::endl;
        v = computeNextLayoutVec(A, basis, xTil, b_x);
        // std::cout << "next x layout vector" << std::endl;
        // std::cout << "v = " << v.transpose() << std::endl;
        x_coord = basis.transpose() * v;



        // improve the y-axis
        yTil = y_coord;
        b_y = computeNextSol(lap, dist, yTil, x_coord, 2); // distPar (alpha) = 2
        // std::cout << "next y layout solution" << std::endl;
        // std::cout << "b_y = " << b_y.transpose() << std::endl;
        v = computeNextLayoutVec(A, basis, yTil, b_y);
        // std::cout << "next y layout vector" << std::endl;
        // std::cout << "y = " << v.transpose() << std::endl;
        y_coord = basis.transpose() * v;

        std::cout << "round #" << i << std::endl;
        std::cout << "x = " << x_coord.transpose() << std::endl;
        if (xTil != x_coord) {
            std::cout << "xtil = x: " << "false" << std::endl;
        } else {
            std::cout << "xtil = x: " << "true" << std::endl;
        }
        std::cout << "y = " << y_coord.transpose() << std::endl;
        if (yTil != y_coord) {
            std::cout << "ytil = y: " << "false" << std::endl;
        } else {
            std::cout << "ytil = y: " << "true" << std::endl;
        }
        if ((xTil != x_coord) || (yTil != y_coord)) {
            std::cout << "not terminate" << std::endl;
        } else {
            std::cout << "terminated" << std::endl;
            break;
        }
        i++;
        ter++;
    // }

    }
}