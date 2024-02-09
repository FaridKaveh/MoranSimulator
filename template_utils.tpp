
#include <iostream>
#include <vector>

template<typename T>
void printVector(const std::vector<T>& vec) {
    std::cout << "[ ";
    for (const auto& elem : vec) {
        std::cout << elem << " ";
    }
    std::cout << "]" << std::endl;
}

template<typename T>
void printVectorOfVectors(const std::vector<std::vector<T>>& vecOfVecs) {
    std::cout << "{ " << std::endl;
    for (const auto& vec : vecOfVecs) {
        printVector(vec);
    }
    std::cout << "}" << std::endl;
}