#pragma once
#include <util.hpp>
#include <instance.hpp>

class SimulatedAnnealing 
{
    public:
        SimulatedAnnealing(Instance instance, int max_time);
        ~SimulatedAnnealing() {}

        void initialize(double initialTemperature, double coolingRate);

        void optimize();

        Instance get_best_solution();

        void setInitialSolution(Instance ins);


    private:
        Instance current_solution;
        Instance best_solution;
        int max_time;
        TimeVar start_time;
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