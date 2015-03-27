/**
 * Declare layout drawing header
 */


#ifndef DRAW_LAYOUT
#define DRAW_LAYOUT

void setPointsAttributes();
void drawNodes(Eigen::VectorXd & x_coord, Eigen::VectorXd & y_coord);
void drawEdges(Eigen::MatrixXd edges, \
  Eigen::VectorXd & x_coord, Eigen::VectorXd & y_coord);
void drawLayout(Graph::Graph &g, \
    Eigen::VectorXd & x_coord, Eigen::VectorXd & y_coord);

#endif