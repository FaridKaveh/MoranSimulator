#ifndef UTILS_H
#define UTILS_H

#include <vector> 

template <typename T>
void printVector(const std::vector<T>& vec);

template <typename T> 
void printVectorOfVectors(const std::vector< std::vector<T> >& vecOfVecs);

template <typename T>
int countNonZeroEntries(const std::vector<T>& vec); 

template <typename T>
int binarySearch(const T& num, const std::vector<T>& vec);

#include "template_utils.tpp"

#endif