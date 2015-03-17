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
#include "hde.h"
#include "laplacian.h"

#include "subspace_iter.h"


int main(int argc, char** argv) {
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
    std::vector< std::vector<double> > lap = Laplacian(g);

    // test space iteration
    SubspaceIteration(lap, low_eigen);
    printMat(low_eigen);
    
    return 0; // end of main program
}