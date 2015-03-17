/**
 * Implement basis vector operation
 */
#ifndef VECTOR
#define VECTOR <vector>
#include VECTOR
#endif
#ifndef IOSTREAM
#define IOSTREAM <iostream>
#include IOSTREAM
#endif
#ifndef MATH
#define MATH <math.h>
#include MATH
#endif

/********************************************
    Perform inner product on given vectors
    Returns: computed inner product
 ********************************************/
double innerProduct(std::vector<double> & vec1, std::vector<double> & vec2)
{
    double dotVal = 0;
    for (int i=0; i<vec1.size(); ++i) {
        dotVal += vec1[i] * vec2[i];
    }

    return dotVal;
}


/************************************************
    Perform scalar multiplication on given vec
    Returns: computed vector
 ************************************************/
std::vector<double> scalarMultiply(double scalar, std::vector<double> & vec)
{
    std::vector<double> smVec (vec.size(), 0);
    for (int i=0; i<vec.size(); ++i) {
        smVec[i] = scalar * vec[i];
    }

    return smVec;
}


/***************************************
    Get the norm of the given vector
    Returns: norm
 ***************************************/
double norm(std::vector<double> & vec)
{
    int sqrSum = 0;
    for (int i=0; i<vec.size(); ++i) {
        sqrSum += vec[i]*vec[i];
    }
    std::cout << "norm = " << sqrSum << std::endl;
    return sqrt(sqrSum);
}


/***************************************
    Show the given vector's elements
    Returns: string
 ***************************************/
void printVec(std::vector<double> & vec)
{
    for (std::vector<double>::iterator it=vec.begin(); \
         it!=vec.end(); \
         ++it) {
        std::cout << (*it) << " ";
    }
    std::cout << std::endl;
}

/***************************************
    normalize the vector
    Returns: string
 ***************************************/
void normalizeVec(std::vector<double> & vec)
{
    double normOfVec = norm(vec);
    for (std::vector<double>::iterator it=vec.begin(); \
         it!=vec.end(); \
         ++it) {
        (*it) = (*it) / normOfVec;
    }

}