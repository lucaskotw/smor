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
#include <Eigen/Dense>
#include "all_pair_shortest_path.h"
#include "hde.h"
#include "subspace_iter.h"
#include "two_dim_stress_subspace.h"

// Package for OpenGL
#include <GL/glew.h>
#include <GL/freeglut.h>


#define WINDOW_TITLE_PREFIX "2D subspace stress layout"

int
  InitialWidth = 800,
  InitialHeight = 600,
  WindowHandle = 0;

// pre-declaration of Open GL
void InitializeDrawing(int, char**);
void InitWindow(int, char**);
void ResizeFunction(int, int);
void RenderFunction(void);




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
  g.showGraph();
  // G = CreateGraph(D);



  /* ---------------------------------- *\
      Preliminary Drawing
  \* ---------------------------------- */
  // preprocessing: get all-pair shortest path
  Eigen::MatrixXd dist = allPairShortestPath(g);
  std::cout << "Distance Matrix" << std::endl;
  std::cout << dist << std::endl;

  // test HDE
  Eigen::MatrixXd low_eigen = HDE(g, 3);


  // test Laplacian
  Eigen::MatrixXd lap = Laplacian(g, 2);
  std::cout << "Appropriate Laplcian" << std::endl;
  std::cout << lap << std::endl;

  // test space iteration
  SubspaceIteration(lap, low_eigen);
  Eigen::VectorXd x_coord = low_eigen.row(0);
  Eigen::VectorXd y_coord = low_eigen.row(1);
  std::cout << "previous coordinates" << std::endl;
  std::cout << "x:" << x_coord.transpose() << std::endl;
  std::cout << "y:" << y_coord.transpose() << std::endl;

  // // test 2d stress minimization
  twoDimStressSubspace(g, lap, dist, low_eigen, x_coord, y_coord);
  std::cout << "result coordinates" << std::endl;
  std::cout << "x:" << x_coord.transpose() << std::endl;
  std::cout << "y:" << y_coord.transpose() << std::endl;
  // int t = 10;
  // X = InitialPlacement(G, t) // Not Preliminary Drawing


  /* -------- *\
      Layout
  \* -------- */
  
  // StressMajorizationLayout(G, X, t)

  /* ---------------- *\
      Draw the graph
  \* ---------------- */

  InitializeDrawing(argc, argv);
  // DrawLayout(X)





  return 0; // end of main program
}

/**
 * Initialze the Drawing Process and Provide Open GL basic information
 */
void InitializeDrawing(int argc, char** argv)
{
  InitWindow(argc, argv);

  std::cout << "--------------------------------" << std::endl;
  std::cout << "|* Initialize Drawing Process *|" << std::endl;
  std::cout << "--------------------------------" << std::endl;
  std::cout << "INFO: OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
 
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
}


/**
 * Create Basic Window and Run the Rending Process
 */
void InitWindow(int argc, char** argv)
{
  glutInit(&argc, argv);
  
  glutInitContextVersion(4, 1); // Todo: present the version of the OpenGL?
  glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);
  glutInitContextProfile(GLUT_CORE_PROFILE);
 
  glutSetOption(
    GLUT_ACTION_ON_WINDOW_CLOSE,
    GLUT_ACTION_GLUTMAINLOOP_RETURNS
  );
  
  glutInitWindowSize(InitialWidth, InitialHeight);
 
  glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
 
  WindowHandle = glutCreateWindow(WINDOW_TITLE_PREFIX);
 
  if (WindowHandle < 1) {
    std::cout << "ERROR: Could not create a new rendering window." << std::endl;
    exit(EXIT_FAILURE);
  }
 
  glutReshapeFunc(ResizeFunction);
  glutDisplayFunc(RenderFunction);
}


/**
 * Dealing with the Action While User Resize the Window
 */
void ResizeFunction(int Width, int Height)
{
  InitialWidth = Width;
  InitialHeight = Height;
  glViewport(0, 0, InitialWidth, InitialHeight);
}


/**
 * Rendering Process
 */
void RenderFunction(void)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
 
  glutSwapBuffers();
  glutPostRedisplay();
}