/**
 * Thesis Layout
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


    /*************
     * Partition *
     *************/
    Eigen::VectorXd partition(nodeNums);
    partitionGraph(g, partition, 4); // 4 is the number of partition
}