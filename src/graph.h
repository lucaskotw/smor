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
        std::vector<int> adj(int s);
        int deg(int s);
        std::vector<double> BFS(int s);
        void showGraph();
};


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
  Get the neighbor of given source
************************************************************/
std::vector<int> Graph::adj(int s) {
    std::vector<int> neighbors;
    int curr_size = neighbors.size();
    for (std::vector<Edge>::iterator it=Edges.begin(); it!=Edges.end(); ++it) {
        if (it->u == s) {
            neighbors.push_back(it->v);
        } else if (it->v == s) {
            neighbors.push_back(it->u);
        }
    }
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
std::vector<double> Graph::BFS(int s)
{
    std::vector<double> dist(numNodes, 0);
    std::queue<int> Q;
    std::vector<bool> explored(numNodes, false);
    Q.push(s);
    explored[s] = true;

    // initialize message
    // std::cout << "BFS start at source: " << s << std::endl;
    // std::cout << "explored status: ";
    // for (int i=0; i<explored.size(); ++i) {
    //     if (explored.at(i)) {
    //         std::cout << "t ";
    //     } else {
    //         std::cout << "f ";
    //     }
    // }
    // std::cout << std::endl;
    while (!Q.empty()) {
        int v = Q.front();
        Q.pop();
        // std::cout << "Process: " << v << std::endl;
        std::vector<int> nbors = Graph::adj(v);
        // std::cout << "Neighbors: ";
        // for (std::vector<int>::iterator it=nbors.begin(); it!=nbors.end(); ++it) {
        //     std::cout << *it << " ";
        // }
        // std::cout << std::endl;

        for (std::vector<int>::iterator it=nbors.begin(); it!=nbors.end(); ++it) {
            if (!explored.at(*it)) {
                Q.push(*it);
                explored[*it] = true;
                int weight = Graph::getWeight(v, *it);
                // std::cout << "edge weight of (" << v << ", " << *it << "):" \
                //             << weight << std::endl;
                if (weight != 0) {
                    dist[*it] = dist[v] + weight;
                }
            }
        }
    }

    // std::cout << "distance to source " << s << std::endl;
    // for (std::vector<double>::iterator it=dist.begin(); it!=dist.end(); ++it) {
    //     std::cout << *it << " ";
    // }
    // std::cout << std::endl;

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