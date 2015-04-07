/**
 * Declare layout drawing header
 */


#ifndef DRAW_LAYOUT
#define DRAW_LAYOUT

void setPointsAttributes();
void drawNodes(Eigen::MatrixXd & coord);
void drawEdges(Eigen::MatrixXd edges, Eigen::MatrixXd & coord);
void drawLayout(Graph::Graph &g, Eigen::MatrixXd & coord);

#endif