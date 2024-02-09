#include <iostream> 
#include <random> //random generation tools
#include <functional> // std::bind
#include <vector>
#include "utils.h" //print_vector

int main() { 
    
    std::random_device rd; //true random seed
    // int seed = 1;
    std::default_random_engine engine(rd()); //pseudo random generator

    int population = 5; 
    std::vector<int> family_count; 
    std::vector<int> intervals; 
    intervals.reserve(population); 

    for (unsigned i = 0; i < population; ++i){ 
        intervals.push_back(i);
        family_count.push_back(1);
    }

    std::exponential_distribution<double> death_dist (population); //exp dist with rate population

    auto death_event_gen = std::bind(death_dist, engine);

    for (unsigned i = 0; i < 10; ++i){ 
        std::cout << death_event_gen() << std::endl;

        std::piecewise_constant_distribution<double> transition_dist (intervals.begin(), intervals.end(),
        family_count.begin()); //modify the dist to use the family count vector as weights

        int death = transition_dist(engine); 
        int replace = transition_dist(engine);

        --family_count.at(death); 
        ++family_count.at(replace); 
        
        printVector(family_count);
        
    }

    return 0;
}