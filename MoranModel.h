#ifndef MORAN_MODEL_H
#define MORAN_MODEL_H

#include <vector>
#include <array>

class MoranProcess{
/* When a MoranProcess instance is declared, the constructor runs the process and 
stores a vector of arrays that records the history. The statistics can all be inferred
 from that vector */
private:
    int population; 
    int events;
    std::vector <int> event_history; 
    std::vector<double> event_times;
    void generatePath();
public:
    MoranProcess(const int& pop,const int& event_num): population(pop), events(event_num){
        generatePath();
    };
    void regeneratePath(){generatePath();};
    void getFamilyHistories();
    int getPopulation(){return this -> population;};
    int getPathLength(){return this -> events;};
    
};

#endif