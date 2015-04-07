/*
 * Implement stress majorization
 */
#ifndef DENSE
#define DENSE <Eigen/Dense>
#include DENSE
#endif
#ifndef FSTREAM
#define FSTREAM <fstream>
#include FSTREAM
#endif
#ifndef IOSTREAM
#define IOSTREAM <iostream>
#include IOSTREAM
#endif
// #ifndef GRAPH
// #define GRAPH "graph.hpp"
// #include GRAPH
// #endif
#include "lap.hpp"
#ifndef LAP
#define LAP "lap.hpp"
#include LAP
#endif
#define THRESHOLD 0.01


/* Use to remove the row */
void removeRow(Eigen::MatrixXd & matrix, unsigned int rowToRemove)
{
    unsigned int numRows = matrix.rows()-1;
    unsigned int numCols = matrix.cols();

    if( rowToRemove < numRows )
        matrix.block(rowToRemove, 0, numRows-rowToRemove, numCols) = matrix.block(rowToRemove+1, 0, numRows-rowToRemove, numCols);

    matrix.conservativeResize(numRows,numCols);
    std::cout << "current matrix" << std::endl;
    std::cout << matrix << std::endl;
}


/* Use to remove the column */
void removeColumn(Eigen::MatrixXd & matrix, unsigned int colToRemove)
{
    unsigned int numRows = matrix.rows();
    unsigned int numCols = matrix.cols()-1;

    if( colToRemove < numCols )
        matrix.block(0,colToRemove,numRows,numCols-colToRemove) = matrix.block(0,colToRemove+1,numRows,numCols-colToRemove);

    matrix.conservativeResize(numRows,numCols);
    std::cout << "current matrix" << std::endl;
    std::cout << matrix << std::endl;
}


double stress(Eigen::MatrixXd & dist, Eigen::MatrixXd & coord, double distParam)
{
    double stress = 0.0;
    int nNodes = coord.rows();
    for (int i=0; i<nNodes; ++i) {
        for (int j=i+1; j<nNodes; ++j) {
            if (i != j) {
                stress += std::pow(dist(i, j), -1*distParam) * \
                    std::pow( ((coord.row(i) - coord.row(j)).norm() - dist(i, j)), 2 );
            }
        }
    }

    return stress;
}



void stressMajorization(Graph::Graph & g, \
    Eigen::MatrixXd & dist, \
    Eigen::MatrixXd & coord, \
    std::ofstream & logFile, \
    double distParam, \
    double threshold) {

    if (!logFile.is_open()) {
        std::cout << "logFile file is not opened!" << std::endl;
        return;
    }
    // Create weight laplacian matrix
    Eigen::MatrixXd wLap = wLaplacian(g, dist, 2);
    double preStress = stress(dist, coord, distParam);
        std::cout << "weighted laplacian matrix" << std::endl;
        std::cout << wLap << std::endl;
        std::cout << "fix weighted laplacian matrix" << std::endl;
        std::cout << wLap.block(1, 1, wLap.rows()-1, wLap.cols()-1) << std::endl;
    Eigen::MatrixXd iterCoord(g.getNumNodes()-1, 2);
    iterCoord = coord.block(1, 0, coord.rows()-1, coord.cols());
    iterCoord = wLap.block(1, 1, wLap.rows()-1, wLap.cols()-1).ldlt().solve(iterCoord);
    coord.fill(0);
    coord.block(1, 0, coord.rows()-1, coord.cols()) = iterCoord;
    double aftStress = stress(dist, coord, distParam);
        std::cout << "iter coord: " << std::endl;
        std::cout <<  iterCoord << std::endl;
        std::cout << "coordinate: " << std::endl;
        std::cout <<  coord << std::endl;
    std::cout << "round 1 stress = " << aftStress << std::endl;
    logFile << "round 1 stress = " << aftStress << std::endl;


    // First Iteration
    double epsl = threshold;
    
    Eigen::MatrixXd iLap(wLap.rows(), wLap.cols());
    Eigen::MatrixXd pSol(wLap.rows(), wLap.cols());
    int i = 2;
    std::cout << "threshold = " << (preStress-aftStress)/preStress << std::endl;
    while ( true ) {
        iLap = iterLayoutLaplacian(g, dist, coord, distParam);
        // std::cout << "iter laplacian" << std::endl;
        // std::cout << iLap << std::endl;
        pSol = iLap * coord;
        iterCoord = wLap.block(1, 1, iLap.rows()-1, iLap.cols()-1)\
            .ldlt().solve(pSol.block(1, 0, coord.rows()-1, coord.cols()));
        // assign preStress based on current iteration
        preStress = aftStress;
        coord.fill(0);
        coord.block(1, 0, coord.rows()-1, coord.cols()) = iterCoord;
        // assign aftStress after coord assign
        aftStress = stress(dist, coord, distParam);
        std::cout << "round " << i << " stress = " << aftStress << std::endl;
        logFile << "round " << i << " stress = " << aftStress << std::endl;
        std::cout << "threshold = " << (preStress-aftStress)/preStress << std::endl;
        logFile << "threshold = " << (preStress-aftStress)/preStress << std::endl;
        // std::cout << "iter coord: " << std::endl;
        // std::cout <<  iterCoord << std::endl;
        // std::cout << "coordinate: " << std::endl;
        // std::cout <<  coord << std::endl;
        if ((preStress-aftStress)/preStress < epsl) {
            break;
        }
        ++i;
    }
    // record coordinates after stress majorization
    logFile << "coordinates: x, y " << std::endl;
    logFile << coord << std::endl;
    
}