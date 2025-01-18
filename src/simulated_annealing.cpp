#include <simulated_annealing.hpp>
#include <util.hpp>

void SimulatedAnnealing::initialize(double initialTemperature, double coolingRate) {
    this->initial_temperature = initialTemperature;
    this->cooling_rate = coolingRate;
    this->temperature = initialTemperature;
}

SimulatedAnnealing::SimulatedAnnealing(Instance instance) : current_solution(instance), best_solution(instance) {
}

int rand(int a, int b) {
    return a + rand() % (b - a + 1);
}

void SimulatedAnnealing::optimize() {
    while(temperature > 1) {
        update_solution();
        update_temperature();
    }
}

Instance SimulatedAnnealing::get_best_solution() {
    return best_solution;
}

void SimulatedAnnealing::setInitialSolution(Instance ins) {
    current_solution = ins;
    best_solution = ins;
}

double SimulatedAnnealing::acceptance_probability(double delta, double temperature) {
    if(delta < 0) {
        return 1;
    }
    return exp(-delta/temperature);
}

void SimulatedAnnealing::update_temperature() {
    temperature *= cooling_rate;
}

void SimulatedAnnealing::update_solution() {
    Instance new_solution = current_solution;
    seq_pair new_seq = new_solution.get_seq();

    int i = rand() % 3;

    if(i == 0) {
        int a = rand(0, new_seq.f.size() - 1);
        int b = rand(0, new_seq.f.size() - 1);
        while(a == b) {
            b = rand(0, new_seq.f.size() - 1);
        }
        swap(new_seq.f[a], new_seq.f[b]);
        new_solution.set_seq(new_seq);
    } else if(i == 1) {
        int a = rand(0, new_seq.f.size() - 1);
        int b = rand(0, new_seq.f.size() - 1);
        while(a == b) {
            b = rand(0, new_seq.f.size() - 1);
        }
        swap(new_seq.s[a], new_seq.s[b]);
        new_solution.set_seq(new_seq);
    } else {
        int a = rand() % new_seq.f.size();
        new_solution.flip_block(a);
    }


    double delta = new_solution.get_area() - current_solution.get_area();
    if(acceptance_probability(delta, temperature) > (double)rand()/RAND_MAX) {
        update_current_solution(new_solution);
    }

    if(current_solution.get_area() < best_solution.get_area()) {
        update_best_solution(current_solution);
    }
}

void SimulatedAnnealing::update_best_solution(Instance ins) {
    best_solution = ins;
}

void SimulatedAnnealing::update_current_solution(Instance ins) {
    current_solution = ins;
}