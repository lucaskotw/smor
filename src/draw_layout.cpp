/**
 * Implement layout drawing functions
 */


// Package for OpenGL
#ifndef GLFW
#define GLFW <GLFW/glfw3.h>
#include GLFW
#endif
#ifndef DENSE
#define DENSE <Eigen/Dense>
#include DENSE
#endif
#ifndef GRAPH
#define GRAPH "graph.hpp"
#include GRAPH
#endif
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 800

void setPointsAttributes()
{
  glEnable(GL_POINT_SMOOTH);
  glPointSize(10);
}


void drawNodes(Eigen::MatrixXd & coord)
{
  double coord_max = coord.maxCoeff();
  glBegin(GL_POINTS);

    glColor3f(0.5f, 0.5f, 0.5f);
    for (int i=0; i<coord.rows(); ++i) {
      glVertex2f(coord(i, 0)/coord_max, coord(i, 1)/coord_max);
    }

  glEnd();
}


void drawEdges(Eigen::MatrixXd edges, Eigen::MatrixXd & coord)
{
  double coord_max = coord.maxCoeff();
  glBegin(GL_LINES);

    glColor3f(0.5f, 0.5f, 0.5f);
    double pt1;
    double pt2;
    for (int i=0; i<edges.rows(); ++i) {
      pt1 = edges(i, 0);
      pt2 = edges(i, 1);
      glVertex2f(coord(pt1, 0)/coord_max, coord(pt1, 1)/coord_max);
      glVertex2f(coord(pt2, 0)/coord_max, coord(pt2, 1)/coord_max);
      // std::cout << "edges size=" << i << std::endl;
    }
    

  glEnd();
}


void drawLayout(Graph::Graph &g, Eigen::MatrixXd & coord)
{


  GLFWwindow* window;

  /* Initialize the library */
  if (!glfwInit())
      exit(1);
      // return -1;

  /* Create a windowed mode window and its OpenGL context */
  window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "2D Stress Layout", NULL, NULL);
  if (!window)
  {
      glfwTerminate();
      exit(1);
      // return -1;
  }

  /* Make the window's context current */
  glfwMakeContextCurrent(window);


  /* Loop until the user closes the window */
  while (!glfwWindowShouldClose(window))
  {
    /* Render here */

    // glfwGetFramebufferSize(window, &width, &height);
    // glViewport(0, 0, width, height);
    setPointsAttributes();

    // set frame background color
    glClearColor( 1.0f, 1.0f, 1.0f, 1.0f );
    glClear(GL_COLOR_BUFFER_BIT);


    drawNodes(coord);
    drawEdges(g.getEdges(), coord);

    


    /* Swap front and back buffers */
    glfwSwapBuffers(window);

    /* Poll for and process events */
    glfwPollEvents();
  }

  glfwTerminate();
}