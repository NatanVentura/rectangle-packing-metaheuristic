#include <evolutionary_algorithm.hpp>
#include <util.hpp>

EvolutionaryAlgorithm::EvolutionaryAlgorithm(vector<double> w, vector<double> h) {
    if (w.size() != h.size()) { 
        throw std::invalid_argument("Invalid instance: w and h must have the same size");
    }
    this->w = w; 
    this->h = h; 
    this->numberOfBlocks = w.size(); 
    this->rng = std::mt19937(std::random_device{}()); 
}

void EvolutionaryAlgorithm::initialize(int populationSize, int generations, double mutationRate, double crossoverRate) {
    this->populationSize = populationSize;
    this->generations = generations;
    this->mutationRate = mutationRate;
    this->crossoverRate = crossoverRate;
}

double EvolutionaryAlgorithm::calculateFitness(Instance &individual) {
    return individual.get_area();
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

    Instance offspring(this->w, this->h);
    seq_pair temp = parent1.get_seq();
    seq_pair temp2 = parent2.get_seq();

    set<int> usedF(temp.f.begin() + start, temp.f.begin() + end + 1);
    set<int> usedS(temp.s.begin() + start, temp.s.begin() + end + 1);

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

    offspring.set_seq(temp);
    return offspring;
}



Instance EvolutionaryAlgorithm::select(vector<double> &fitness) {
    const int tournamentSize = 3;
    uniform_int_distribution<int> indexDist(0, this->populationSize - 1);

    vector<int> tournamentIndices;
    for (int i = 0; i < tournamentSize; ++i) {
        int idx = indexDist(this->rng);
        tournamentIndices.push_back(idx);
    }

    int bestIndex = tournamentIndices[0];
    for (int i = 1; i < tournamentSize; ++i) {
        if (fitness[tournamentIndices[i]] < fitness[bestIndex]) {
            bestIndex = tournamentIndices[i];
        }
    }

    return this->population[bestIndex];
}

void EvolutionaryAlgorithm::initializePopulation() {
    this->population.clear();
    for (int i = 0; i < this->populationSize; ++i) {
        Instance individual(this->w, this->h);
        this->population.push_back(individual);
    }
}

Instance EvolutionaryAlgorithm::get_best_solution() {

    initializePopulation();

    for (int gen = 0; gen < this->generations; gen++) {
        vector<double> fitness(this->populationSize);
        for (int i = 0; i < this->populationSize; i++) {
            fitness[i] = calculateFitness(this->population[i]);
        }

        auto bestIt = min_element(fitness.begin(), fitness.end());
        int bestIndex = distance(fitness.begin(), bestIt);

        vector<Instance> newPopulation;
        newPopulation.push_back(this->population[bestIndex]);

        while ((int)newPopulation.size() < this->populationSize) {
            Instance parent1 = select(fitness);
            Instance parent2 = select(fitness);

            Instance offspring = crossover(parent1, parent2);
            mutate(offspring);

            newPopulation.push_back(offspring);
        }

        population = newPopulation;
    }

    vector<double> finalFitness(this->populationSize);
    for (int i = 0; i < this->populationSize; ++i) {
        finalFitness[i] = calculateFitness(this->population[i]);
    }

    auto bestIt = min_element(finalFitness.begin(), finalFitness.end());
    int bestIndex = distance(finalFitness.begin(), bestIt);
    return this->population[bestIndex];
}