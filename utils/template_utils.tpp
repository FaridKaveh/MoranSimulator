
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
        return -1;
    } else if (left >= vec.size()) {
        return vec.size();
    } else {
        if (vec[left] > target) return left -1;

        return left;
    }
}
