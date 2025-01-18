#pragma once
#include <util.hpp>
#include <instance.hpp>

class SimulatedAnnealing {
    public:

        SimulatedAnnealing(Instance instance);

        ~SimulatedAnnealing() {}

        void initialize(double initialTemperature, double coolingRate);

        void optimize();

        Instance get_best_solution();

        void setInitialSolution(Instance ins);


    private:
        Instance best_solution;
        Instance current_solution;
        double initial_temperature;
        double cooling_rate;
        double temperature;
        double acceptance_probability(double delta, double temperature);
        void update_temperature();
        void update_solution();
        void update_best_solution();
        void update_current_solution(Instance ins);
        void update_best_solution(Instance ins);
};