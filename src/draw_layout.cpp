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


void drawLayout(Graph::Graph &g, \
  Eigen::VectorXd & x_coord, Eigen::VectorXd & y_coord)
{
    GLFWwindow* window;

  /* Initialize the library */
  if (!glfwInit())
      exit(1);
      // return -1;

  /* Create a windowed mode window and its OpenGL context */
  window = glfwCreateWindow(800, 800, "2D Stress Layout", NULL, NULL);
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


    drawNodes(x_coord, y_coord);
    drawEdges(g.getEdges(), x_coord, y_coord);

    


    /* Swap front and back buffers */
    glfwSwapBuffers(window);

    /* Poll for and process events */
    glfwPollEvents();
  }

  glfwTerminate();
}