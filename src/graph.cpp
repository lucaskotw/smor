/**
 * Implement Graph Class
 *
 * Todo:
 *   1. Consider namespace and template
 *   2. use costom queue instead of std one
 */
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

#include "graph.hpp"




/************************************************************
  Graph Constructor
************************************************************/
Graph::Graph(int size)
{
    if (size < 2) numNodes = 2; // minimum of number of node is 2
    else numNodes = size;

}


/************************************************************
  Graph Destructor
************************************************************/
Graph::~Graph()
{
    Edges.clear();
}


/************************************************************
  add edge to the graph object
************************************************************/
void Graph::addEdge(int u, int v, int w)
{
    int currSize = Edges.size();
    struct Edge givenEdge = {u, v, w};
    Edges.resize(currSize++);
    Edges.push_back(givenEdge);
}


/************************************************************
  Get the number of nodes in the graph
************************************************************/
int Graph::getNumNodes()
{
    return numNodes;
}


/************************************************************
  Get the weight of given two end points
************************************************************/
int Graph::getWeight(int u, int v)
{
    for (std::vector<Edge>::iterator it=Edges.begin(); it!=Edges.end(); ++it) {
        if ( (it->u == u && it->v == v) || (it->u == v && it->v == u) ) {
            return it->w;
        }
    }
    return 0; // represent the invalid end point assignment
}


/************************************************************
  Get the weight of given two end points
************************************************************/
Eigen::MatrixXd Graph::getEdges() {

    Eigen::MatrixXd edges(Edges.size(), 2);

    int i = 0;
    for (std::vector<Edge>::iterator it=Edges.begin(); it!=Edges.end(); ++it) {
        edges(i, 0) = it->u;
        edges(i, 1) = it->v;
        i++;
    }

    return edges;
}


/************************************************************
  Get the neighbor of given source
************************************************************/
Eigen::VectorXd Graph::adj(int s) {
    std::vector<double> t_nbors;

    for (std::vector<Edge>::iterator it=Edges.begin(); it!=Edges.end(); ++it) {
        if (it->u == s) {
            t_nbors.push_back(it->v);
        } else if (it->v == s) {
            t_nbors.push_back(it->u);
        }
    }
    double * ptr = &t_nbors[0];
    Eigen::Map<Eigen::VectorXd> neighbors (ptr, t_nbors.size());
    // std::cout << "adj of node " << s << std::endl;
    // std::cout << neighbors.transpose() << std::endl;

    return neighbors;
}


/************************************************************
  Get the degree of given vertex
************************************************************/
int Graph::deg(int s) {

    return Graph::adj(s).size();
}


/************************************************************
  Run Breadth-first Search and returns the distance of the
  nodes 
************************************************************/
Eigen::VectorXd Graph::BFS(int s)
{
    Eigen::VectorXd dist(numNodes);
    dist.fill(0);
    std::queue<int> Q;
    std::vector<bool> explored(numNodes, false);
    Q.push(s);
    explored[s] = true;

    while (!Q.empty()) {
        int v = Q.front();
        Q.pop();

        Eigen::VectorXd nbors = Graph::adj(v);

        for (int i=0; i<nbors.size(); ++i) {
            if ( !explored.at(nbors(i)) ) {
                Q.push(nbors(i));
                explored[nbors(i)] = true;
                // Consider only unit weight
                int weight = Graph::getWeight(v, nbors(i));

                if (weight != 0) {
                    dist(nbors(i)) = dist(v) + weight;
                }
            }
        }
        // std::cout << "current dist" << s << std::endl;
        // std::cout << dist.transpose() << std::endl;
        // std::cout << "current explored" << std::endl;
        // for (int j=0; j<explored.size(); ++j) {
        //     if (explored[j]) {
        //         std::cout << "t";
        //     } else {
        //         std::cout << "f";
        //     }
        //     std::cout << " ";
        // }
        // std::cout << std::endl;
    }

    std::cout << "BFS from source " << s << std::endl;
    // std::cout << dist.transpose() << std::endl;

    return dist;
}


/************************************************************
  present the current graph
************************************************************/
void Graph::showGraph()
{
    std::cout << "Graph Info" << std::endl;
    std::cout << "# of Nodes: " << numNodes << std::endl;
    std::cout << "Edges:" << std::endl;
    std::cout << "u v w" << std::endl;
    std::cout << "-----" << std::endl;
    for (std::vector<Edge>::iterator it=Edges.begin(); it!=Edges.end(); ++it) {
        std::cout << it->u << " " << it->v << " " << it->w << std::endl;
    }
}