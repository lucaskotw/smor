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
#include <fstream>
#include <ctime>
#include <string>

// Custom header file
#include "all_pair.hpp"
#include "sm.hpp"
#include "lap.hpp"
#include "load_graph.hpp"
#include "draw_layout.hpp"


int main(int argc, char** argv)
{

    /*************************
     * Record the coordinate *
     *************************/
    std::ofstream logFile;
    std::string dataName = argv[1];
    std::string logFileName = dataName + "_coord.log";
    logFile.open(logFileName, std::ios::out|std::ios::app);
    std::time_t t = std::time(0);
    std::cout << "start time: " << std::asctime(std::localtime(&t));
    logFile << "start time: " << std::asctime(std::localtime(&t));



    /******************
     * Load the graph *
     ******************/
    Eigen::MatrixXd mat;
    int nodeNums;
    mmRead(argv[1], mat, nodeNums);
    logFile << "File: " << argv[1] << std::endl;
    Graph::Graph g(nodeNums);
    std::cout << "number of nodes = " << nodeNums << std::endl;
    CreateGraph(g, mat);
    g.showGraph();


    /******************
     * Initial Layout *
     ******************/
    Eigen::MatrixXd coord(nodeNums, 2);
    // randomly giving coordinates
    for (int i=0; i<nodeNums; ++i) {
        coord(i, 0) = rand()%100/50.0;
        coord(i, 1) = rand()%100/50.0;
    }
    coord(0, 0) = 0;
    coord(0, 1) = 0;
    std::cout << "initial coordinates:" << std::endl;
    std::cout << coord << std::endl;


    /**************************
     * Run Stress Majorization *
     **************************/
    // solving the linear system
    Eigen::MatrixXd dist = allPairShortestPath(g);
    std::cout << "distance matrix:" << std::endl;
    t = std::time(0);    
    logFile << "bfs end time: " << std::asctime(std::localtime(&t));
    // std::cout << dist << std::endl;
    std::cout << "round 0 stress = " << std::endl;
    std::cout << stress(dist, coord, 2) << std::endl;
    logFile << "coordinates: x, y " << std::endl;
    logFile << coord << std::endl;

    t = std::time(0);
    logFile << "stress majorization start time: " << std::asctime(std::localtime(&t));
    stressMajorization(g, dist, coord, logFile, 2);
    t = std::time(0);
    std::cout << "end time: " << std::asctime(std::localtime(&t));
    logFile << "end time: " << std::asctime(std::localtime(&t));

    /******************
     * Draw the graph *
     ******************/
    drawLayout(g, coord);

    /**********************************
     * Post processing of the process *
     **********************************/
    logFile.close();

    return 0;
}