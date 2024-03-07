
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

template<typename T>
int binarySearch(const T& target, const std::vector<T>& vec) {

    /*Searches sorted vector vec for target. If target is found in vec it 
    returns the index of target in vec. If vec[0] <= target <= vec[vec.size()-1], 
    then it returns index i such that vec[i] < target < vec[i+1]. Else if target < vec[0]
    the function returns 0. Else we have target > vec[vec.size()-1] and the function returns
    vec.size()-1.  */
    
    int left = 0;
    int right = vec.size() - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (vec[mid] == target) {
            return mid;
        } else if (vec[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    if (right < 0) {
        return 0;
    } else if (left >= vec.size()) {
        return vec.size()-1;
    } else {
        if (vec[left] > target) return left -1;

        return left;
    }
}
