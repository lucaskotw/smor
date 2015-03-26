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
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <Eigen/Dense>


#include "all_pair.hpp"
#include "hde.hpp"
#include "lap.hpp"
#include "subspace_iter.hpp"
#include "two_d_stress.hpp"
#include "load_graph.hpp"

// Package for OpenGL
#include <GLFW/glfw3.h>


void setPointsAttributes()
{
  glEnable(GL_POINT_SMOOTH);
  glPointSize(20);
}


void drawNodes(Eigen::VectorXd & x_coord, Eigen::VectorXd & y_coord)
{
  glBegin(GL_POINTS);

    glColor3f(0.5f, 0.5f, 0.5f);
    for (int i=0; i<x_coord.size(); ++i) {
      glVertex2f(x_coord(i)/3, y_coord(i)/3);
    }

  glEnd();
}


void drawEdges(Eigen::MatrixXd edges, \
  Eigen::VectorXd & x_coord, Eigen::VectorXd & y_coord)
{

  glBegin(GL_LINES);

    glColor3f(0.5f, 0.5f, 0.5f);
    double pt1;
    double pt2;
    for (int i=0; i<edges.rows(); ++i) {
      pt1 = edges(i, 0);
      pt2 = edges(i, 1);
      glVertex2f(x_coord(pt1)/3, y_coord(pt1)/3);
      glVertex2f(x_coord(pt2)/3, y_coord(pt2)/3);
      // std::cout << "edges size=" << i << std::endl;
    }
    

  glEnd();
}


int main(int argc, char** argv)
{
  /**
   * 20150315: layout psudocode
   */ 
  
  /* ---------------------------------- *\
      Loading data to create the graph
  \* ---------------------------------- */
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
  
  std::cout << "edges:" << std::endl;
  std::cout << g.getEdges() << std::endl;


  // // C-style (due to mmio is c-based code)
  // Eigen::MatrixXd mat;
  // int nodeNums;
  // char path[] = "data/karate.mtx";
  // mmRead(path, mat, nodeNums);
  // Graph::Graph g(nodeNums);
  // CreateGraph(g, mat);
  // g.showGraph();
  



  /* ---------------------------------- *\
      Preliminary Drawing
  \* ---------------------------------- */
  // preprocessing: get all-pair shortest path
  Eigen::MatrixXd dist = allPairShortestPath(g);
  std::cout << "Distance Matrix" << std::endl;
  std::cout << dist << std::endl;

  // test HDE
  Eigen::MatrixXd low_eigen = HDE(g, 50);


  // // test Laplacian
  // Eigen::MatrixXd lap = Laplacian(g, 2);
  // std::cout << "Appropriate Laplcian" << std::endl;
  // std::cout << lap << std::endl;

  // // test space iteration
  // SubspaceIteration(lap, low_eigen);
  // Eigen::VectorXd x_coord = low_eigen.row(0);
  // Eigen::VectorXd y_coord = low_eigen.row(1);
  // std::cout << "previous coordinates" << std::endl;
  // std::cout << "x: " << x_coord.transpose() << std::endl;
  // std::cout << "y: " << y_coord.transpose() << std::endl;

  // // test 2d stress minimization
  // twoDimStressSubspace(g, lap, dist, low_eigen, x_coord, y_coord);
  // std::cout << "result coordinates" << std::endl;
  // std::cout << "x: " << x_coord.transpose() << std::endl;
  // std::cout << "y: " << y_coord.transpose() << std::endl;
  // // int t = 10;
  // // X = InitialPlacement(G, t) // Not Preliminary Drawing


  // /* -------- *\
  //     Layout
  // \* -------- */
  
  // // StressMajorizationLayout(G, X, t)

  // /* ---------------- *\
  //     Draw the graph
  // \* ---------------- */

  // // InitializeDrawing(argc, argv);
  // // DrawLayout(X)
  // GLFWwindow* window;

  // /* Initialize the library */
  // if (!glfwInit())
  //     return -1;

  // /* Create a windowed mode window and its OpenGL context */
  // window = glfwCreateWindow(800, 800, "2D Stress Layout", NULL, NULL);
  // if (!window)
  // {
  //     glfwTerminate();
  //     return -1;
  // }

  // /* Make the window's context current */
  // glfwMakeContextCurrent(window);


  // /* Loop until the user closes the window */
  // while (!glfwWindowShouldClose(window))
  // {
  //   /* Render here */

  //   // glfwGetFramebufferSize(window, &width, &height);
  //   // glViewport(0, 0, width, height);
  //   setPointsAttributes();

  //   // set frame background color
  //   glClearColor( 1.0f, 1.0f, 1.0f, 1.0f );
  //   glClear(GL_COLOR_BUFFER_BIT);


  //   drawNodes(x_coord, y_coord);
  //   drawEdges(g.getEdges(), x_coord, y_coord);

    


  //   /* Swap front and back buffers */
  //   glfwSwapBuffers(window);

  //   /* Poll for and process events */
  //   glfwPollEvents();
  // }

  // glfwTerminate();





  return 0; // end of main program
}
