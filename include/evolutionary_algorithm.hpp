#pragma once
#include <util.hpp>
#include <instance.hpp>

class EvolutionaryAlgorithm {
    public:
        EvolutionaryAlgorithm(vector<double> w, vector<double> h, int maxTime);
        ~EvolutionaryAlgorithm() {}
        void initialize(int populationSize, int generations, double mutationRate, double crossoverRate);
        Instance get_best_solution();

    private:
        vector<Instance> population;
        int populationSize;
        int generations;
        int numberOfBlocks;
        int max_time;
        TimeVar start_time;
        vector<double> w, h;
        double mutationRate;
        double crossoverRate;
        std::mt19937 rng;
        void initializePopulation ();
        Instance select(vector<double> &fitness);
        Instance crossover(Instance &parent1, Instance &parent2);
        void mutate(Instance &individual);
        double calculateFitness (Instance &individual);
};