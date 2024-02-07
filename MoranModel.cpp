#include <iostream> 
#include <random> //random generation tools
#include <functional> // std::bind
#include <vector>

int main() { 
    
    std::random_device rd; //true random seed
    std::default_random_engine engine(rd()); //pseudo random generator

    int population = 5; 
    std::exponential_distribution<double> death_dist (population); //exp dist with rate population

    auto death_event_gen = std::bind(death_dist, engine);

    for (unsigned i = 0; i < 10; ++i){ 
        std::cout << death_event_gen() << std::endl;
    }

    return 0;
}