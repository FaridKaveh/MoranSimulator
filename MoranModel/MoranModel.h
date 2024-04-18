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
    int equil_events = -1;
    int mut_number = 0;
    bool to_equil = false;

    std::vector<double> event_times;
    std::vector <int> event_history; 
    std::vector < std::vector<int> > mutations;

    void generateTree(const unsigned& seed, const bool& to_equil=false);
    void generateMuts(const unsigned& seed);

    
    void generatePath( unsigned seed = 0){
        generateTree(seed, to_equil);
        generateMuts(seed);
    };

    
public:
    MoranProcess(const int& pop,const int& event_num, const bool& to_equil): 
    population(pop), events(event_num), to_equil(to_equil){
        generatePath();
    };

    void regeneratePath(){
        equil_events = -1;
        generatePath();}

    
    int getPopulation(){return this -> population;}
    int getPathLength(){return this -> events;}
    int getMutNumber(){return this -> mut_number;}
    
    int getEquilEvents(){return this -> equil_events;}

    std::vector<double> getEventTimes(){return this -> event_times;}
    std::vector<int> getEventHistory(){return this -> event_history;}
    std::vector< std::vector<int> > getMutations(){return this -> mutations;}

    int calculateFamilyHistories(bool draw = false);
    int calcualteSegregatingSites(
        const std::vector< std::vector<int> >& sample = std::vector< std::vector<int> > ()
    );
    std::vector<int> calculateSiteFrequencySpectrum( 
        const std::vector< std::vector<int> >& sample = std::vector < std::vector<int> > ()
    ); 
    std::vector<int> calculateMutationFrequencySpectrum(
        const std::vector< std::vector<int> >& sample = std::vector < std::vector<int> > ()
    );

    
    std::vector< std::vector<int> > buildCoalescentTree(int level = -1);
    bool isAtEquilibrium();
     
};

#endif