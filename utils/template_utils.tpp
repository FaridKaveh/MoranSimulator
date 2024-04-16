
#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <algorithm>

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
    then it returns index i such that vec[i-1] < target < vec[i]. Else if target < vec[0]
    the function returns 0. Else we have target > vec[vec.size()-1] and the function returns
    vec.size()-1.  */
    

    //TO DO: Test this function throughly including edge cases.
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
        // if (vec[left] > target) return left;

        return left;
    }
}

template <typename T>
T getMaxOfVector(const std::vector<T>& vec){
    if (vec.empty()){
        throw std::runtime_error("getMaxOfVector: input vector cannot be empty.");
    }

    T max_element = *vec.begin();
    std::for_each(vec.begin()+1, vec.end(), 
    [&](const T& val){max_element = std::max(max_element, val);});

    return max_element;
}

template <typename T> 
void addVectors(const std::vector<T>& summand, std::vector<T>& vec){ 
    if (summand.size() != vec.size()) {
        throw std::runtime_error("addVectors: vector dimensions do not match");
    }

    for (size_t i = 0; i < vec.size(); i++) {
        vec.at(i) += summand.at(i);
    }
}

template <typename T> 
std::vector<T> sampleWithReplacement(
    const std::vector<T>& population,
    const int& sample_size,
    const std::vector<double>& weights
){ 
std::vector<T> sample;

if (sample_size >= population.size()) {
    throw std::runtime_error("sampleWithReplacement: sample size must be smaller than population size");
}

if (weights.empty()) {
    // Use uniform distribution
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0, population.size() - 1);

    for (int i = 0; i < sample_size; i++) {
        int index = dist(gen);
        sample.push_back(population.at(index));
    }
} else {
    if (weights.size() != population.size()) {
        throw std::runtime_error("takeSample: weights size must match population size");
    }

    // Normalise weights
    double sum = std::accumulate(weights.begin(), weights.end(), 0.0);

    std::vector<double> normalisedWeights;
    normalisedWeights.reserve(weights.size());
    for (const auto& weight : weights) {
        normalisedWeights.push_back(weight / sum);
    }

    // Create piecewise distribution
    std::random_device rd;
    std::mt19937 gen(rd());
    std::piecewise_constant_distribution<> weight_dist (
        population.size()-1,
        0,
        population.size()-1,
        [&](const int& idx){return normalisedWeights.at(idx);}
    );

    // Sample according to weights
    for (int i = 0; i < sample_size; i++) {
        int randomValue = static_cast<int> (weight_dist(gen));
        sample.push_back(population.at(randomValue));
    }
}

return sample;
}


//sampleWithoutReplacement is not working.
template <typename T>
std::vector<T> sampleWithoutReplacement(
    const std::vector<T>& population,
    const int& sample_size
){ 

    unsigned seed1 = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine engine(seed1);

    std::vector<int> perm; 
    perm.reserve(population.size());
    
    for (unsigned i = 0; i < population.size(); ++i) perm.push_back(i);

    std::vector<T> sample;
    sample.reserve(sample_size);

    std::shuffle(perm.begin(), perm.end(), engine);
    for (unsigned i = 0; i < sample_size; ++i) sample.push_back(population.at(perm.at(i)));

    return sample;
}