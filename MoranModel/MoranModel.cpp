#include <iostream> 
#include <random> //random generation tools
#include <functional> // std::bind
#include <vector>
#include <array>
#include <algorithm> //std::for_each, std::remove_if
#include "/home/farid/Documents/git/MoranSimulator/utils/utils.h" //print_vector
#include "MoranModel.h"


typedef std::vector < std::vector<int> > TwoDIntVec;

void MoranProcess::generateTree(unsigned seed){ 

    event_history.clear();
    event_times.clear();
    event_history.reserve(events);
    event_times.reserve(events);

    
    std::random_device rd; //true random seed
    std::default_random_engine engine (rd()); //pseudo random generator
    

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

void MoranProcess::generateMuts(unsigned seed){

    mutations.assign(population, std::vector<int> ());
    
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


std::vector<int> MoranProcess::calculateSiteFrequencySpectrum(
    const std::vector< std::vector<int> >& sample){ 

    std::vector< std::vector <int> > mut_vector;

    //if no sample is provided, use the whole population
    mut_vector = sample.empty() ? mutations : sample;
    int sample_size = mut_vector.size();
    std::vector<int> occurrences;
    unsigned size_of_occurrences;

    for (unsigned i =0; i < sample_size; ++i){ 
        size_of_occurrences += mut_vector.at(i).size();
    }
    occurrences.reserve(size_of_occurrences);

    for (std::vector<int> individual: mut_vector){
        occurrences.insert(occurrences.end(), individual.begin(),individual.end());
    }
    //order mutations from earliest to most recent 
    std::sort(occurrences.begin(), occurrences.end());

    std::vector<int>::reverse_iterator it = occurrences.rbegin();
    int current_mut = *it;
    int last_mut = *it;
    int count = 1;

    std::vector<int> sfs (population, 0);
    //iterate backwards through occurrences and stop when you find a fixed mutation.
    while (it != occurrences.rend()){
        
        last_mut = *it;  
        current_mut = *(++it); 

        if (last_mut == current_mut){ 

            ++count;
            //mutation is fixed -> all earlier (surviving) mutations also fixed
            if (count == sample_size) break; 

        } else { 
            ++sfs.at(count-1);
            count = 1; 
        } 
        
    }    

    int non_fixed_muation_count = 0; 

    for (int i = 0; i < sample_size-1; ++i){ 
        non_fixed_muation_count += i*sfs.at(i);
    }

    sfs.at(sample_size-1) = (occurrences.size() - non_fixed_muation_count)/sample_size;

    return sfs;
}

int MoranProcess::calcualteSegregatingSites(
    const std::vector< std::vector<int> >& sample){ 
    
    std::vector<int> sfs = calculateSiteFrequencySpectrum(sample);
    int segregating_sites = std::accumulate(sfs.begin(), sfs.end()-1, 0);

    return segregating_sites;
}

std::vector<int> MoranProcess::calculateMutationFrequencySpectrum(
    const TwoDIntVec& sample
){  
    TwoDIntVec mut_vector = sample.empty() ? mutations : sample;

    int max_mutation = 0; 

    std::for_each(mut_vector.begin(), mut_vector.end(),
    [&](const std::vector<int>& mutations){
        if (!mutations.empty()) max_mutation = std::max(max_mutation, mutations.back());
    });

    std::vector<int> freq_vector (max_mutation, 0);

    for (unsigned i = 0; i < mut_vector.size(); ++i){ 

        std::vector<int> individual = mut_vector.at(i);
        for (unsigned j = 0; j < individual.size(); ++j){ 
            ++freq_vector.at(individual.at(j)-1);
        }
    }

    
    if (freq_vector.empty()) { 
        std::cout << "Warning: empty frequency vector. Possibly due to a small number of events or a \
        small sample." << std::endl;
        return freq_vector;
    }

    //disregard fixed and lost mutations.
    freq_vector.erase(std::remove_if(freq_vector.begin(), freq_vector.end(), 
    [&](const int& val){
        return ( val == 0 || val == sample.size());
        }), 
        freq_vector.end());

    if (freq_vector.empty()) { 
        std::cout << "Warning: empty frequency vector. All mutations were fixed." << std::endl;
    }
    return freq_vector;
}

std::vector < std::vector<int> > MoranProcess::buildCoalescentTree(int level){ 
    if (level == -1){ 
        level = events; 
    }

    std::vector< std::vector <int> > coalescent_tree; 

    return coalescent_tree;
}