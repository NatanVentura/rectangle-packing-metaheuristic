#pragma once
#include <util.hpp>
#include <instance.hpp>

class EvolutionaryAlgorithm {
public:
    EvolutionaryAlgorithm(
        vector<int64_t> w,
        vector<int64_t> h,
        int maxTime,
        int populationSize,
        int generations,
        double mutationRate,
        double crossoverRate);
    ~EvolutionaryAlgorithm() {}
    Instance get_best_solution();

private:
    const Instance &get_current_best();
    void initializePopulation();
    Instance &select();
    Instance crossover(Instance &parent1, Instance &parent2);
    void mutate(Instance &individual);

    vector<Instance> population;
    int populationSize;
    int generations;
    int numberOfBlocks;
    int max_time;
    mt19937 rng;
    TimeVar start_time;
    vector<int64_t> w, h;
    double mutationRate;
    double crossoverRate;
};