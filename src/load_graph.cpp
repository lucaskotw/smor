/**
 * Perform the Three basic process to read matrix market file
 * 1. Process the first line of file and identify the matrix type
 *    (mm_read_banner())
 * 2. Use a type-specific function to skip the optional comments and process the
 *    matrix size information (mm_read_mtx_crd_size())
 * 3. read the numerical data, one matrix entry per line
 *
 * Todo:
 *   1. Since the matrix market format identify dense and sparse matrix,
 *      crate a condition check
 *   2. Constriants that matrix should be read only if it's symmertic.
 */
#ifndef E_DENSE
#define E_DENSE <Eigen/Dense>
#include E_DENSE
#endif
#ifndef IOSTREAM
#define IOSTREAM <iostream>
#include IOSTREAM
#endif
#ifndef C_IO
#define C_IO <stdio.h>
#include C_IO
#endif
extern "C"
{
    #include "mmio.h"    
}
#ifndef GRAPH
#define GRAPH "graph.hpp"
#include GRAPH
#endif

int mmRead(char *path, Eigen::MatrixXd & mat, int & nodeNums)
{
    std::cout << path << std::endl;
    FILE * f;
    MM_typecode matcode; // this var will record the type of the matrix

    // error handling while fopen
    if ((f = fopen("data/karate.mtx", "r")) == NULL)
    {
        std::cout << "error opening file" << std::endl;
        return -1;
    }


    // read in the type of the matrix
    if (mm_read_banner(f, &matcode) != 0)
    {
        std::cout << "Could not process Matrix Market banner" << std::endl;
        return -1;
    }
    // print the type of the matrix
    std::cout << "Matrix Type:" << std::endl;
    std::cout << mm_typecode_to_str(matcode) << std::endl;

    // get the matrix size and resize the input matrix
    int ret_code;
    int Rows;
    int Cols;
    int nZero;
    if ((ret_code = mm_read_mtx_crd_size(f, &Rows, &Cols, &nZero)) !=0)
    {
        exit(1);
    }
    mat.resize(Rows, Cols);
    std::cout << "Matrix Size = " << Rows << " x " << Cols << std::endl;

    nodeNums = Rows; // set up the node numbers

    // read in the matrix content
    int rElem;
    int cElem;
    for (int i=0; i<nZero; ++i)
    {
        fscanf(f, "%d %d\n", &rElem, &cElem);
        // mat index start from 0, but matrix format index from 1
        mat(rElem-1, cElem-1) = 1;
        if (mm_is_symmetric(matcode))
        {
            mat(cElem-1, rElem-1) = 1;
        }

    }

    // print out the created matrix
    std::cout << "Input Adjacency Matrix" << std::endl;
    std::cout << mat << std::endl;
    return 0; // success
}


int CreateGraph(Graph::Graph & g, Eigen::MatrixXd & adj_mat)
{
    for (int i=0; i<adj_mat.rows(); ++i)
    {
        for (int j=0; j<=i; ++j) {
            if (adj_mat(i, j) != 0) {
                g.addEdge(i, j, 1);
            }
        }
    }
    return 0;
}