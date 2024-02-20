#include <iostream>
#include "MoranModel.h"
#include <algorithm>

int main(){ 

    int N = 0;
    int population = 0;
    int events = 0;
    
    std::cout << "Population: ";
    std::cin >> population;
    
    std::cout << std::endl << "Number of events: ";
    std::cin >> events;
     
    std::cout << std::endl << "Indicate number of runs: "; 
    std::cin >> N;
    
    std::cout << std::endl;

    MoranProcess moran(population, events); 
    std::vector<int> total_gen;
    total_gen.reserve(N);
    for (int i = 0; i < N; ++i){
        total_gen.push_back(moran.getFamilyHistories());

        moran.regeneratePath();
    }
    
    double mean = 0;
    double second_moment = 0;

    std::for_each(total_gen.begin(), total_gen.end(), [&](const int& gens){
        mean += gens;
        second_moment += gens*gens;
        // std::cout << "square = " <<  gens*gens << std::endl;
        // std::cout << "second_moment= " << second_moment << std::endl;
    });

    mean /= N;
    second_moment /= N;
    double variance = second_moment - mean*mean;

    printf("mu = %f, sigma^2 = %f\n", mean, variance);
    return 0;
}
