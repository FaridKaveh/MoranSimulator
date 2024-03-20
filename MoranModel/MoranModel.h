#ifndef MORAN_MODEL_H
#define MORAN_MODEL_H

#include <vector>
#include <array>

constexpr double THETA = 1.5;

class MoranProcess{
/* When a MoranProcess instance is declared, the constructor runs the process and 
stores a vector of arrays that records the history. The statistics can all be inferred
 from that vector */
private:
    int population; 
    int events;
    int mut_number = 0;

    std::vector<double> event_times;
    std::vector <int> event_history; 
    std::vector < std::vector<int> > mutations;
    
    void generatePath(unsigned seed = 0){
        generateTree(seed);
        generateMuts(seed);
    };

    void generateTree(unsigned seed);
    void generateMuts(unsigned seed);

public:
    MoranProcess(const int& pop,const int& event_num): population(pop), events(event_num){
        generatePath();
    };

    void regeneratePath(){generatePath();}

    
    int getPopulation(){return this -> population;}
    int getPathLength(){return this -> events;}
    int getMutNumber(){return this -> mut_number;}

    std::vector<double> getEventTimes(){return this -> event_times;}
    std::vector<int> getEventHistory(){return this -> event_history;}
    std::vector< std::vector<int> > getMutations(){return this -> mutations;}

    int calculateFamilyHistories(bool draw = false);
    int calcualteSegregatingSites();
    std::vector<int> calculateSiteFrequencySpectrum(); 

    
    std::vector< std::vector<int> > buildCoalescentTree(int level = -1);
    
    
};

#endif