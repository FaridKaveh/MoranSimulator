#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <vector>
#include <string>
#include "MoranConfig.h"
#include "/home/farid/Documents/git/MoranSimulator/utils/utils.h"
#include "/home/farid/Documents/git/MoranSimulator/MoranModel/MoranModel.h"


int main(int argc, char* argv[]){ 


    std::cout << "VERSION " << MoranModel_VERSION_MAJOR << "."
    << MoranModel_VERSION_MINOR << std::endl; 

    if (argc != 4) { 
        std::cout << "Incorrect number of arguments\n";
        std::cout << argc - 1 << " arguments given, 3 required.\n"; 
        std::cout << "Usage: " << "./MoranSimulator population events runs\n";

        return 1;
    }
    

    int runs = atoi(argv[3]);
    int events = atoi(argv[2]);
    int population = atoi(argv[1]);
    
    // int runs = 100; 
    // int events = 20000; 
    // int population = 100;

    printf("POPULATION = %i, ", population);
    printf("EVENTS = %i, ", events);
    printf("RUNS = %i \n", runs); 



    MoranProcess moran(population, events, true); 

    int average_quotient = 0; 
    int average_remainder = 0;
    int seg_sites = 0;

    std::vector< std::vector<int> > sample; 
    int sample_size = 10;
    sample.reserve(sample_size);

    int time_to_equil = 0;
    int average_t_quotient = 0; 
    int average_t_remainder = 0;

    for (unsigned i = 0; i < runs; ++i){ 
        
        // std::cout << "Event to equil: " << moran.getEquilEvents() << std::endl;
        sample = sampleWithoutReplacement(moran.getMutations(), sample_size);

        seg_sites = moran.calcualteSegregatingSites(sample);
        time_to_equil = moran.getEquilEvents();

        average_t_quotient += time_to_equil / runs;
        average_t_remainder += time_to_equil % runs;

        average_quotient += seg_sites / runs;  
        average_remainder += seg_sites % runs;
        moran.regeneratePath();
    }

    double average_mutations = average_quotient + 
        static_cast<double> (average_remainder) / runs; 
    
    double average_time = average_t_quotient + 
        static_cast<double> (average_t_remainder) / runs;
    

    std::cout << "<S> = " << average_mutations << std::endl; 
    std::cout << "<T> = " << average_time << std::endl; 

    
    return 0;
}
