/**
 * Declare HDE function
 */
#include <algorithm>
#include <stdlib.h>     /* srand, rand */
#ifndef GRAPH
#define GRAPH "graph.h"
#include GRAPH
#endif
#include "argmax.h"

#define INF 200000


std::vector< std::vector<double> > HDE(Graph::Graph g, int m)
{
    // Return High-Dimensional Embedding of the graph with m-dim assign
    //
    // Args:
    //   g: given graph with node and edge attributes
    //   m: nums of iteration
    //
    // Returns:
    //   basis vectors of subspace

    // int pivot_idx = rand() % g.getNumNodes(); // initial first pivot index
    int pivot_idx = 2;
    std::vector<double> dist (g.getNumNodes(), INF);
    std::vector<double> dist_star;
    std::vector< std::vector<double> > basis(m, \
                                             std::vector<double>(g.getNumNodes()));
    for (int i=0; i<m; ++i) {
        // compute all distance based on subspace basis vectors to pivot node
        // via BFS
        dist_star = g.BFS(pivot_idx); // todo: does not need to clear 
                                      // dist_star?
        for (int j=0; j<g.getNumNodes(); j++) {
            basis[i][j] = dist_star[j]; // todo: change to vector standard
                                        // usage
            dist[j] = std::min(dist[j], basis[i][j]);
        }

        // choose next pivot
        pivot_idx = ArgMax(dist);

    }
    std::cout << "computed hde basis:" << std::endl;
    std::cout << "-------------------" << std::endl;
    for (int i=0; i<basis.size(); ++i) {
      for (int j=0; j<basis[i].size(); ++j) {
        std::cout << basis[i][j] << " ";
      }
      std::cout << std::endl;
    }

    return basis;
}