/**
 * Declare Graph Class
 *
 * Todo:
 *   1. Consider namespace and template
 *   2. use costom queue instead of std one
 */
#ifndef GRAPH_H
#define GRAPH_H

#ifndef VECTOR
#define VECTOR <vector>
#include VECTOR
#endif
#ifndef E_DENSE
#define E_DENSE <Eigen/Dense>
#include E_DENSE
#endif
#ifndef IOSTREAM
#define IOSTREAM <iostream>
#include IOSTREAM
#endif
#ifndef QUEUE
#define QUEUE <queue>
#include QUEUE
#endif

/********************
  Declare edge struct
*********************/
struct Edge
{
    int u; // First End Point
    int v; // Second End Point
    int w; // weight on edge
};






/************************************************************
  Class Graph represents a Graph(V, E) having vertices V and
  edges E.
************************************************************/
class Graph
{
    private:
        int numNodes;
        std::vector<Edge> Edges;
    public:
        Graph(int size);
        ~Graph();
        void addEdge(int u, int v, int w);
        int getNumNodes();
        int getWeight(int u, int v);
        Eigen::MatrixXd getEdges();
        Eigen::VectorXd adj(int s);
        int deg(int s);
        Eigen::VectorXd BFS(int s);
        void showGraph();
};


#endif