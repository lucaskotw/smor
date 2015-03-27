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

// C-based header file
extern "C" {
  #include <stdio.h>
  #include <stdlib.h>
}


// C++ based header file

// Custom header file
#include "graph.hpp"
#include "load_graph.hpp"
#include "draw_layout.hpp"


int main(int argc, char** argv)
{
    /******************
     * Load the graph *
     ******************/
    Eigen::MatrixXd mat;
    int nodeNums;
    char path[] = "data/karate.mtx";
    mmRead(path, mat, nodeNums);
    Graph::Graph g(nodeNums);
    CreateGraph(g, mat);
    g.showGraph();

    /******************
     * Initial Layout *
     ******************/
    Eigen::VectorXd x_coord(nodeNums);
    Eigen::VectorXd y_coord(nodeNums);
    // randomly giving coordinates
    for (int i=0; i<nodeNums; ++i) {
        x_coord(i) = rand()%100/50.0;
        y_coord(i) = rand()%100/50.0;
    }
    std::cout << "initial coordinates:" << std::endl;
    std::cout << "x = " << x_coord.transpose() << std::endl;
    std::cout << "y = " << y_coord.transpose() << std::endl;

    /******************
     * Draw the graph *
     ******************/
     drawLayout(g, x_coord, y_coord);
}