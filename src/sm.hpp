#ifndef SM_H
#define SM_H

void removeRow(Eigen::MatrixXd & matrix, unsigned int rowToRemove);
void removeColumn(Eigen::MatrixXd & matrix, unsigned int colToRemove);
double stress(Eigen::MatrixXd & dist, Eigen::MatrixXd & coord, double distParam);

void stressMajorization(Graph::Graph & g, \
    Eigen::MatrixXd & dist, \
    Eigen::MatrixXd & coord, \
    std::ofstream & logFile, \
    double distParam);
#endif