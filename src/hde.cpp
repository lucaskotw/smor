/**
 * Implement HDE function
 */
#include <algorithm>
#ifndef GRAPH
#define GRAPH "graph.hpp"
#include GRAPH
#endif


#define INF 200000


int ArgMax(Eigen::VectorXd vec)
{
    int maxIdx = 0;
    int maxVal = 0;
    for (int i=0; i<vec.size(); ++i) {
        if (vec(i) > maxVal) {
            maxIdx = i;
            maxVal = vec(i);
        }
    }

    return maxIdx;
}


Eigen::MatrixXd HDE(Graph::Graph & g, int m)
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
    Eigen::VectorXd dist(g.getNumNodes());
    dist.fill(INF);
    Eigen::VectorXd dist_star(g.getNumNodes());
    dist_star.fill(INF);
    m = std::min(g.getNumNodes(), m);
    std::cout << "low dimension m = " << std::endl;
    Eigen::MatrixXd basis(m, g.getNumNodes());
    for (int i=0; i<m; ++i) {
        // compute all distance based on subspace basis vectors to pivot node
        // via BFS
        dist_star = g.BFS(pivot_idx); // todo: does not need to clear 
                                      // dist_star?

        for (int j=0; j<g.getNumNodes(); j++) {
            basis(i, j) = dist_star(j); // todo: change to vector standard
                                        // usage
            dist(j) = std::min(dist(j), basis(i, j));
        }

        // choose next pivot
        pivot_idx = ArgMax(dist);

    }
    std::cout << "computed hde basis:" << std::endl;
    std::cout << "-------------------" << std::endl;
    std::cout << basis << std::endl;


    return basis;
}