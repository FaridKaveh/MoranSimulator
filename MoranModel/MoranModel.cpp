#include <iostream> 
#include <random> //random generation tools
#include <functional> // std::bind
#include <vector>
#include <array>
#include <algorithm> //std::for_each
#include "/home/farid/Documents/git/MoranSimulator/utils/utils.h" //print_vector
#include "MoranModel.h"

void MoranProcess::generateTree(){ 

    event_history.clear();
    event_times.clear();
    event_history.reserve(events);
    event_times.reserve(events);

    std::random_device rd; //true random seed
    std::default_random_engine engine(rd()); //pseudo random generator

    std::exponential_distribution<double> death_dist (population); //exp dist with rate population
    auto death_event = std::bind(death_dist, engine);

    std::uniform_int_distribution<int> select_dist(0, population-1);
    auto select_member = std::bind(select_dist, engine);

    for (unsigned i = 0; i < events; ++i){ 
        event_times.push_back(death_event());
        event_history.push_back(select_member());
        event_history.push_back(select_member()); 
    }
}

void MoranProcess::generateMuts(){

    mutations.assign(population, std::vector<double> ());
    
    std::random_device rd;
    std::default_random_engine engine(rd());
 
    double rate = events * THETA/(2*population); 

    std::poisson_distribution<int> mut_dist(rate);
    mut_number = mut_dist(engine); 
    
    
    std::vector<double> weights (events, 0.0);
    
    for (int i = 0; i < events; ++i){ 
        weights.at(i) = i > 0 ? weights.at(i-1)+event_times.at(i) : event_times.at(i); 
    }  

    std::uniform_int_distribution<> mut_drop(0, events-1); 
    double draw;
    int box;
    std::vector<int> allocations (events, 0);

    for (int i = 0; i < mut_number; i++){ 

        box = mut_drop(engine); 

        try{ 
        ++allocations.at(box);
        }

        catch (...){ 
            printf("box = %i, draw = %f\n", box, draw);
        }
    }

     
    std::uniform_int_distribution<> pick_line (0,population-1); 
    std::uniform_real_distribution<> mutant_id (0,1); 
    int line; 
    unsigned id = 0; 

    for (unsigned i = 0; i < events; ++i) { 

        line = event_history.at(2*i + 1);

        while (allocations.at(i) > 0){
        
        mutations.at(line).push_back(++id);
        --allocations.at(i);

        }

        mutations.at(event_history.at(2*i)) = mutations.at(event_history.at(2*i+1));
    }
}

int MoranProcess::calculateFamilyHistories(bool draw){ 

    std::vector<double> family_placement; //keep track of which individuals belong to which families
    family_placement.reserve(population);
    for (unsigned i = 0; i < population; ++i){ 
        family_placement.push_back(i);
    }

    std::vector<double> family_count (population, 1); //keep track of how many individuals in each family

    unsigned non_zero_count = population; //number of extant family lines
    int i = 0; 
    unsigned dying; 
    unsigned replicating;
    
    while (i < event_history.size()/2 && non_zero_count > 1){ 
        if (draw) printVector(family_placement); 
        
        if (event_history.at(2*i) != event_history.at(2*i+1)){ 
            dying = event_history.at(2*i);
            replicating = event_history.at(2*i+1);
            int dying_fam = family_placement.at(dying); //dying family
            int replicating_fam = family_placement.at(replicating); //replicating family

            --family_count.at(dying_fam);
            ++family_count.at(replicating_fam);

            if (family_count.at(dying_fam) == 0) --non_zero_count;

            family_placement.at(dying) = family_placement.at(replicating);
        }
        ++i;
        
    }

    if (draw) printVector(family_placement);

    return i;
}


std::vector<int> MoranProcess::calcualteSegregatingSites(){ 

    std::vector<int> segregating_sites (population, 0);
    return segregating_sites;
}

std::vector<int> MoranProcess::calculateSiteFrequencySpectrum(){ 
    return std::vector<int> ();
}

std::vector < std::vector<int> > MoranProcess::buildCoalescentTree(int level){ 
    if (level == -1){ 
        level = events; 
    }

    std::vector< std::vector <int> > coalescent_tree; 

    return coalescent_tree;
}