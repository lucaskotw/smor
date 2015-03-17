/**
 * Perform Orthonormalize process
 */
#ifndef VECTOR
#define VECTOR <vector>
#include VECTOR
#endif
#ifndef VECTOROP
#define VECTOROP "vector_op.h"
#include VECTOROP
#endif
#ifndef IOSTREAM
#define IOSTREAM <iostream>
#include IOSTREAM
#endif


void Orthonormalize(std::vector< std::vector<double> > & basis)
{
    int nDim = basis.at(0).size();
    double epsl = 0.001;
    std::vector<double> center_vec(nDim, 1);
    normalizeVec(center_vec);
    std::cout << "center vector: " << std::endl;
    printVec(center_vec);

    double dotVal = 0;    
    std::vector<double> projVal;
    for (int i=0; i<basis.size(); ++i) {
        std::cout << "basis #" << i << std::endl;
        printVec(basis[i]);

        // for each vector in basis, process with center_vec
        dotVal = innerProduct(basis[i], center_vec);
        projVal = scalarMultiply(dotVal, center_vec);
        for (int k=0; k<basis.at(i).size(); ++k) {
            basis[i][k] = basis[i][k] - projVal[k];
        }
        printVec(basis[i]);

        // process with previous vector after process with center_vec
        for (int j=0; j<i; ++j) {
            dotVal = innerProduct(basis[i], basis[j]);
            projVal = scalarMultiply(dotVal, basis[j]);
            for (int k=0; k<basis.at(i).size(); ++k) {
                basis[i][k] = basis[i][k] - projVal[k];
            }
            printVec(basis[i]);
        }

        // remove linearly dependent vectors
        if (norm(basis[i]) < epsl) {

            for (int j=0; j<basis[i].size(); ++j) {
                basis[i][j] = 0;
            }


        } else {
            
            normalizeVec(basis[i]);
        }
    }


    // show the result of orthonormal basis
    std::cout << "Basis after orthornomalizing" << std::endl;
    std::cout << "----------------------------" << std::endl;
    for (std::vector< std::vector<double> >::iterator it1=basis.begin(); \
         it1!=basis.end(); \
         ++it1) {
        for (std::vector<double>::iterator it2=(*it1).begin(); \
             it2!=(*it1).end(); \
             ++it2) {
            std::cout << (*it2) << " ";
        }
        std::cout << std::endl;
    }
}