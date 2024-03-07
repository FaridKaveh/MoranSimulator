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
        std::cout << "Usage: " << "./MoranSimulator population events runs\n";

        return 1;
    }
    
    
    int runs = atoi(argv[3]);
    int events = atoi(argv[2]);
    int population = atoi(argv[1]);
    
    printf("POPULATION = %i, ", population);
    printf("EVENTS = %i, ", events);
    printf("RUNS = %i \n", runs); 


    MoranProcess moran(population, events); 
    std::cout << "S = " << moran.calculateNumberOfMutationEvents() << std::endl; 
    
    return 0;
}
