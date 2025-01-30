#include <evolutionary_algorithm.hpp>
#include <util.hpp>

EvolutionaryAlgorithm::EvolutionaryAlgorithm(
    vector<int64_t> w,
    vector<int64_t> h,
    int maxTime,
    int populationSize,
    int generations,
    double mutationRate,
    double crossoverRate
) {
    if (w.size() != h.size()) { 
        throw std::invalid_argument("Invalid instance: w and h must have the same size");
    }
    this->populationSize = populationSize;
    this->generations = generations;
    this->mutationRate = mutationRate;
    this->crossoverRate = crossoverRate;
    this->w = move(w); 
    this->h = move(h); 
    this->numberOfBlocks = this->w.size(); 
    this->rng = std::mt19937(std::random_device{}()); 
    this->start_time = timeNow();
    this->max_time = maxTime;
}

void EvolutionaryAlgorithm::mutate(Instance &individual) {
    uniform_real_distribution<double> dist(0.0, 1.0);
    uniform_int_distribution<int> indexDist(0, this->numberOfBlocks - 1);

    if (dist(this->rng) > this->mutationRate) return;

    if(dist(this->rng) <= 0.5) {
        seq_pair temp = individual.get_seq();
        int idx1 = indexDist(this->rng);
        int idx2 = indexDist(this->rng);
        swap(temp.f[idx1], temp.f[idx2]);
        idx1 = indexDist(this->rng);
        idx2 = indexDist(this->rng);
        swap(temp.s[idx1], temp.s[idx2]);
        individual.set_seq(temp);
    } else {
        int idx = indexDist(this->rng);
        individual.flip_block(idx);
    }
}

Instance EvolutionaryAlgorithm::crossover(Instance &parent1, Instance &parent2) {
    uniform_real_distribution<double> rateDist(0.0, 1.0);

    if (rateDist(this->rng) >= this->crossoverRate) {
        uniform_real_distribution<double> parentDist(0.0, 1.0);
        return parentDist(this->rng) < 0.5 ? parent1 : parent2;
    }

    int sz = this->numberOfBlocks;
    uniform_int_distribution<int> dist(0, sz - 1);

    int start = dist(this->rng);
    int end = dist(this->rng);
    if (start > end) swap(start, end);

    seq_pair temp = parent1.get_seq();
    const seq_pair &temp2 = parent2.get_seq();

    unordered_set<int> usedF(temp.f.begin() + start, temp.f.begin() + end + 1);
    unordered_set<int> usedS(temp.s.begin() + start, temp.s.begin() + end + 1);

    int indexF = 0;
    for (int value : temp2.f) {
        if (usedF.find(value) == usedF.end()) {
            while (indexF >= start && indexF <= end) {
                ++indexF;
            }
            temp.f[indexF] = value;
            usedF.insert(value);
            ++indexF;
        }
    }

    int indexS = 0;
    for (int value : temp2.s) {
        if (usedS.find(value) == usedS.end()) {
            while (indexS >= start && indexS <= end) {
                ++indexS;
            }
            temp.s[indexS] = value;
            usedS.insert(value);
            ++indexS;
        }
    }

    Instance offspring(this->w, this->h);
    offspring.set_seq(temp);
    return offspring;
}



Instance &EvolutionaryAlgorithm::select() {
    const int tournamentSize = 3;
    uniform_int_distribution<int> indexDist(0, this->populationSize - 1);

    vector<int> tournamentIndices;
    for (int i = 0; i < tournamentSize; ++i) {
        int idx = indexDist(this->rng);
        tournamentIndices.push_back(idx);
    }

    int bestIndex = tournamentIndices[0];
    for (int i = 1; i < tournamentSize; ++i) {
        if(this->population[tournamentIndices[i]].get_area() < this->population[bestIndex].get_area()) {
            bestIndex = tournamentIndices[i];
        }
    }

    return this->population[bestIndex];
}

void EvolutionaryAlgorithm::initializePopulation() {
    this->population.clear();
    for (int i = 0; i < this->populationSize; ++i) {
        Instance individual(this->w, this->h);
        individual.gen_random_seq(i);
        this->population.push_back(move(individual));
    }
}

const Instance &EvolutionaryAlgorithm::get_current_best() {
    int best = 0;
    for(int i = 1; i < this->population.size(); i++) {
        if(this->population[i].get_area() < this->population[best].get_area()) {
            best = i;
        }
    }
    return this->population[best];
}

Instance EvolutionaryAlgorithm::get_best_solution() {

    initializePopulation();

    for (int gen = 0; gen < this->generations; gen++) {
        if(duration(timeNow()-start_time) > max_time){
            break;
        }
        
        vector<Instance> newPopulation;
        newPopulation.push_back(this->get_current_best());

        while ((int)newPopulation.size() < this->populationSize) {
            if(duration(timeNow()-start_time) > max_time){
                break;
            }
            Instance &parent1 = select();
            Instance &parent2 = select();
            Instance offspring = crossover(parent1, parent2);
            mutate(offspring);

            newPopulation.push_back(offspring);
        }

        population = move(newPopulation);
    }

    return this->get_current_best();
}