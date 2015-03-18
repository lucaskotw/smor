/**
 * Collection of matrix operation
 * matrix implementation: vector of vector
 *
 * Todo:
 *   1. examine quadlike multiplication
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


/******************************************************\
    Get corresponding transpose matrix

    Returns: transpose matrix
\******************************************************/
std::vector< std::vector<double> > MatTranspose ( \
    std::vector< std::vector<double> > & xMat)
{
    std::vector< std::vector<double> > xTrans (xMat[0].size(), \
        std::vector<double> (xMat.size(), 0));
    for (int i=0; i<xMat[0].size(); ++i) {
        for (int j=0; j<xMat.size(); ++j) {
            xTrans[i][j] = xMat[j][i];
        }
    }
    return xTrans;
}


/******************************************************\
    Perform matrix multiplication, using MatTranspose

    Returns: result matrix
\******************************************************/
std::vector< std::vector<double> > MatMultiply ( \
    std::vector< std::vector<double> > & aMat, \
    std::vector< std::vector<double> > & bMat)
{
    // declare result matrix first
    std::vector< std::vector<double> > result (aMat.size(), \
        std::vector<double> (bMat[0].size(), 0));

    // transpose second matrix for inner product operation
    std::vector< std::vector<double> > bTrans = MatTranspose(bMat);
    for (int i=0; i<aMat.size(); ++i) {
        for (int j=0; j<bMat[0].size(); ++j) {
            result[i][j] = innerProduct(aMat[i], bTrans[j]);
        }
    }


    return result;

}


/******************************************************\
    Perform quadlike matrix

    Returns: result matrix
\******************************************************/
std::vector< std::vector<double> > QuadMatMultiply ( \
    std::vector< std::vector<double> > & xMat, \
    std::vector< std::vector<double> > & aMat)
{
    // transpose the x and a matrix first for multiplication
    std::vector< std::vector<double> > xTrans = MatTranspose(xMat);

    // compute X^T*A
    std::vector< std::vector<double> > firstMat = MatMultiply(xTrans, aMat);
    std::cout << "first Multiply" << std::endl;
    std::cout << "----------------" << std::endl;
    printMat(firstMat);

    // compute firstMat * X
    std::vector< std::vector<double> > secondMat = MatMultiply(firstMat, xMat);
    std::cout << "second Multiply" << std::endl;
    std::cout << "---------------" << std::endl;
    printMat(secondMat);

    return secondMat;
}