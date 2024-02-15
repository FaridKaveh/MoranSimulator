#include <iostream> 
#include <random> //random generation tools
#include <functional> // std::bind
#include <vector>
#include <array>
#include "utils.h" //print_vector
#include "MoranProcess.h"

void MoranProcess::generatePath(){ 

    event_history.clear();
    event_times.clear();
    event_history.reserve(events);
    event_times.reserve(events);

    std::random_device rd; //true random seed
    std::default_random_engine engine(rd()); //pseudo random generator

    std::exponential_distribution<double> death_dist (population); //exp dist with rate population
    auto death_event = std::bind(death_dist, engine);

    std::uniform_int_distribution<int> select_dist(1, population);
    auto select_member = std::bind(select_dist, engine);

    for (unsigned i = 0; i < population; ++i){ 
        event_times.push_back(death_event());
        event_history.push_back(select_member());
        event_history.push_back(select_member()); 
    }
}

void MoranProcess::getFamilyHistories(){ 

    std::vector<double> family_count (population, 1);
    unsigned non_zero_count = population; //number of extant family lines
    unsigned i = 0; 
    
    while (i < event_history.size()/2 && non_zero_count > 1){ 
        printVector(family_count); 
        // --family_count.at(event_history.at(2*i+1));
        // ++family_count.at(event_history.at(2*i));

        //If a family line had died
        if (family_count.at(event_history.at(2*i+1)) == 0) --non_zero_count;
    }
}

int main() { 
    
    std::random_device rd; //true random seed
    // int seed = 1;
    std::default_random_engine engine(rd()); //pseudo random generator

    int population = 5; 
    int events = 10;
    std::vector<int> family_count; 
    std::vector<int> intervals; 
    intervals.reserve(population); 

    for (unsigned i = 0; i < population; ++i){ 
        intervals.push_back(i);
        family_count.push_back(1);
    }

    std::exponential_distribution<double> death_dist (population); //exp dist with rate population

    auto death_event_gen = std::bind(death_dist, engine);
    std::vector<double> event_times; 
    event_times.reserve(events); 

    for (unsigned i = 0; i < events; ++i){ 
        event_times.push_back(death_event_gen()); 

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