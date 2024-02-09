#ifndef UTILS_H
#define UTILS_H

#include <vector> 

template <typename T>
void printVector(const std::vector<T>& vec);

template <typename T> 
void printVectorOfVectors(const std::vector< std::vector<T> >& vecOfVecs);

#include "template_utils.tpp"

#endif