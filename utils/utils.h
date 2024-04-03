#ifndef UTILS_H
#define UTILS_H

#include <vector> 


// std::vector<int> countFrequencies(const std::vector<int>& vec);

template <typename T>
void printVector(const std::vector<T>& vec);

template <typename T> 
void printVectorOfVectors(const std::vector< std::vector<T> >& vecOfVecs);

template <typename T>
int countNonZeroEntries(const std::vector<T>& vec); 

template <typename T>
int binarySearch(const T& num, const std::vector<T>& vec);

template <typename T> 
T getMaxOfVector(const std::vector<T>& vec); 

template <typename T> 
void addVectors(const T& summand, T& vec);

template <typename T> 
std::vector<T> sampleWithReplacement(
    const std::vector<T>& population,
    const int& sample_size,
    const std::vector<double>& weights = std::vector<double> ());

template <typename T> 
std::vector<T> sampleWithoutReplacement(
    const std::vector<T>& population,
    const int& sample_size
); 

#include "template_utils.tpp"

#endif