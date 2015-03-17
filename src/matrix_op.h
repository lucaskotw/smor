/**
 * Collection of matrix operation
 * matrix implementation: vector of vector
 */
#ifndef VECTOROP
#define VECTOROP "vector_op.h"
#include VECTOROP
#endif


/******************************************\
    Print the given matrix in row-major

    Returns: none
\******************************************/
void printMat (std::vector< std::vector<double> > & mat)
{
    for (std::vector< std::vector<double> >::iterator it=mat.begin(); \
         it!=mat.end(); \
         ++it) {
        printVec(*it);
    }

}


/******************************************************\
    multiply matrix element with scalar element-wise
    Returns: result matrix
\******************************************************/
std::vector< std::vector<double> > MatScalarMultiply (double scalar, \
    std::vector< std::vector<double> > & mat)
{
    std::vector< std::vector<double> > result (mat.size(), \
        std::vector<double> (mat[0].size(), 0));
    for (int i=0; i<mat.size(); ++i) {
        for (int j=0; j<mat[i].size(); ++j) {
            result[i][j] = scalar * mat[i][j];
        }
    }
    return result;
}


/******************************************************\
    perform matrix-vector multiplication between a 
    square matrix and correspoding vector

    Returns: result vector
\******************************************************/
std::vector<double> MatVecMultiply ( \
    std::vector< std::vector<double> > & mat,
    std::vector<double> & vec)
{
    std::vector<double> result;
    for (std::vector< std::vector<double> >::iterator it=mat.begin(); \
        it!=mat.end(); ++it) {
        result.push_back( innerProduct(*it, vec) );
    }
    // std::cout << "result size: " << result.size() << std::endl;
    // printMat(mat);

    return result;
}


/******************************************************\
    Perform matrix subtraction between two squre matrix

    Returns: result matrix
\******************************************************/
std::vector< std::vector<double> > MatSubtract ( \
    std::vector< std::vector<double> > & mat1,
    std::vector< std::vector<double> > & mat2)
{
    std::vector< std::vector<double> > result (mat1.size(), \
        std::vector<double> (mat1[0].size(), 0));
    for (int i=0; i<mat1.size(); ++i) {
        for (int j=0; j<mat1[i].size(); ++j) {
            result[i][j] = mat1[i][j] - mat2[i][j];
        }
    }
    return result;
}


/******************************************************\
    Create identity matrix with given dimension

    Returns: identity matrix
\******************************************************/
std::vector< std::vector<double> > unitMat (int dim)
{
    std::vector< std::vector<double> > unit (dim, std::vector<double> (dim, 0));
    for (int i=0; i<unit.size(); ++i) {
        for (int j=0; j<unit[i].size(); ++j) {
            if (i==j) unit[i][j] = 1;
        }
    }

    return unit;
}