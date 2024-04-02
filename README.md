MoranSimulator is a simulation program for the [Moran process](https://en.wikipedia.org/wiki/Moran_process) with mutations. It can be used to numerically calculate analytically intractable statistics, or otherwise to verify analytic 
results about the Moran process.

You can make and build the project using CMake. You will need to have CMake installed. If you do not have it, you can [download it ](https://cmake.org/download/).
Beware that CMake has several dependencies which will need to be installed first, for example you will need to have a C/C++ compiler installed. 

1. Build using CMake
   
   You will need a CMake version of 3.10 or later. Navigate to the repo directory and use the following commands

   ```
   mkdir build
   cd build
   CMake ../
   CMake --build .
   ```
2. Running MoranSimulator

   The program takes three arguments. The first is two are the population size and the number of events you want to simulate. These are parameters of the model. The third is the number of runs you want to simulate. If you want to calculate
   summary statistics you will probably want to average over more than one simulation. Here is an example on Linux
   ```
   ./MoranSimulator 10 2000 1000
   ```

   will output

```
   VERSION 0.1
   POPULATION = 100, EVENTS = 2000, RUNS = 100 
   <S> = 4.08
```
Here S is the number of segregating sites in the population after the last event. <S\> is the average of this quantity across the 1000 runs. If you want to change what is being calculated, you can go into main and change it to calculate your favourite statistic. 
