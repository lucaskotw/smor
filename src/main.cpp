/**
 * Drawing with clusters overlap removal
 * 1. initial positioning
 * 2. clusters overlap removal
 *   a) bundle the edge with order considering
 * 3. draw the layout
 */

/**
 * Todo:
 *   1. implement stress majorization
 */
#include <iostream>
#include <vector>
#include <queue>
#include <Eigen/Dense>
#include "hde.h"
#include "subspace_iter.h"


int main(int argc, char** argv)
{
    // 20150315: layout psudocode
    // // Create graph with appropriate data structure
    // G = CreateGraph(D);
    // int t = 10;
    // X = InitialPlacement(G, t) // Not Preliminary Drawing


    // // Layout
    
    // StressMajorizationLayout(G, X, t)

    // // Draw the graph
    // DrawLayout(X)

    // create graph
    Graph::Graph g(8);
    g.addEdge(0, 1, 1);
    g.addEdge(0, 2, 1);
    g.addEdge(1, 2, 1);
    g.addEdge(1, 3, 1);
    g.addEdge(1, 4, 1);
    g.addEdge(2, 4, 1);
    g.addEdge(2, 6, 1);
    g.addEdge(2, 7, 1);
    g.addEdge(3, 4, 1);
    g.addEdge(4, 5, 1);
    g.addEdge(6, 7, 1);
    // g.showGraph();


    // test HDE
    std::vector< std::vector<double> > low_eigen;
    low_eigen = HDE(g, 3);

    // test Laplacian
    // std::vector< std::vector<double> > lap = Laplacian(g);

    // test space iteration
    // SubspaceIteration(lap, low_eigen);
    // printMat(low_eigen);


    // test transpose
    std::vector< std::vector<double> > xTransTest (3, \
      std::vector<double> (3, 1));
    xTransTest[0][1] = 7;
    xTransTest[2][1] = 10;
    xTransTest[1][1] = 2;
    xTransTest[1][2] = 3;
    std::cout << "before transpose" << std::endl;
    std::cout << "----------------" << std::endl;
    printMat(xTransTest);
    std::vector< std::vector<double> > xTrans = MatTranspose(xTransTest);
    std::cout << "after transpose" << std::endl;
    std::cout << "----------------" << std::endl;
    printMat(xTrans);


    // test Multiply
    std::vector< std::vector<double> > aMulti (3, \
      std::vector<double> (3, 1));
    aMulti[0][1] = 2;
    aMulti[0][2] = -1;
    aMulti[1][0] = -3;
    aMulti[1][1] = -2;
    aMulti[1][2] = 3;
    aMulti[2][1] = 4;
    aMulti[2][2] = 2;
    std::vector< std::vector<double> > bMulti (3, \
      std::vector<double> (2, 1));
    bMulti[0][1] = 2;
    bMulti[0][2] = -1;
    bMulti[1][0] = -3;
    bMulti[1][1] = -2;
    bMulti[1][2] = 3;


    // test quad Multiply
    std::vector< std::vector<double> > quad = QuadMatMultiply(bMulti, aMulti);
    std::cout << "after quad Multiply" << std::endl;
    std::cout << "-------------------" << std::endl;
    printMat(quad);

    // test eigen
    Eigen::MatrixXd m(2,2);
    m(0,0) = 3;
    m(1,0) = 2.5;
    m(0,1) = -1;
    m(1,1) = m(1,0) + m(0,1);
    std::cout << m << std::endl;

    return 0; // end of main program
}