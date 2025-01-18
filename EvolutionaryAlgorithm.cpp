#include <bits/stdc++.h>

using namespace std;

struct Individual {
    vector<int> p1; 
    vector<int> p2; 
};

vector<vector<int> > constroi_grafo(const Individual &ind) {
    vector<vector<int> > g;
    return g;
}

double calcula(vector<vector<int> > &g) {
    return 0.0;
}

double calculateFitness(const Individual &ind) {
    vector<vector<int> > grafo = constroi_grafo(ind);
    return calcula(grafo);
}

void mutate(Individual &ind, double mutationRate, mt19937 &rng) {
    uniform_real_distribution<double> dist(0.0, 1.0);
    uniform_int_distribution<int> indexDist(0, ind.p1.size() - 1);

    if (dist(rng) < mutationRate) {
        int idx1 = indexDist(rng);
        int idx2 = indexDist(rng);
        swap(ind.p1[idx1], ind.p1[idx2]);
    }

    if (dist(rng) < mutationRate) {
        int idx1 = indexDist(rng);
        int idx2 = indexDist(rng);
        swap(ind.p2[idx1], ind.p2[idx2]);
    }
}

Individual crossover(const Individual &parent1, const Individual &parent2, mt19937 &rng) {
    int sz = parent1.p1.size();
    uniform_int_distribution<int> dist(0, sz - 1);

    int start = dist(rng);
    int end = dist(rng);
    if (start > end) swap(start, end);

    Individual offspring;
    offspring.p1 = vector<int>(sz, -1);
    offspring.p2 = vector<int>(sz, -1);

    for (int i = start; i <= end; ++i) {
        offspring.p1[i] = parent1.p1[i];
        offspring.p2[i] = parent1.p2[i];
    }

    auto fill = [&](vector<int> &child, const vector<int> &parent, const vector<int> &segment) {
        int current = 0;
        for (int i = 0; i < sz; ++i) {
            int value = parent[i];
            if (find(segment.begin() + start, segment.begin() + end + 1, value) == segment.begin() + end + 1) {
                while (child[current] != -1) {
                    current = (current + 1) % sz;
                }
                child[current] = value;
            }
        }
    };

    fill(offspring.p1, parent2.p1, offspring.p1);
    fill(offspring.p2, parent2.p2, offspring.p2);

    return offspring;
}

Individual select(const vector<Individual> &population, const vector<double> &fitness, mt19937 &rng) {
    uniform_real_distribution<double> dist(0.0, 1.0);
    double totalFitness = accumulate(fitness.begin(), fitness.end(), 0.0);

    double target = dist(rng) * totalFitness;
    double cumulative = 0.0;

    for (size_t i = 0; i < population.size(); ++i) {
        cumulative += fitness[i];
        if (cumulative >= target) {
            return population[i];
        }
    }

    return population.back(); 
}

vector<Individual> initializePopulation(int populationSize, int permutationSize, mt19937 &rng) {
    vector<Individual> population(populationSize);
    for (auto &ind : population) {
        ind.p1.resize(permutationSize);
        ind.p2.resize(permutationSize);
        iota(ind.p1.begin(), ind.p1.end(), 0);
        iota(ind.p2.begin(), ind.p2.end(), 0);
        shuffle(ind.p1.begin(), ind.p1.end(), rng);
        shuffle(ind.p2.begin(), ind.p2.end(), rng);
    }
    return population;
}

void runEvolutionaryAlgorithm(int populationSize, int permutationSize, int generations, double mutationRate) {
    random_device rd;
    mt19937 rng(rd());

    vector<Individual> population = initializePopulation(populationSize, permutationSize, rng);

    for (int gen = 0; gen < generations; ++gen) {
        
        vector<double> fitness(populationSize);
        for (int i = 0; i < populationSize; ++i) {
            fitness[i] = calculateFitness(population[i]);
        }

      vector<Individual> newPopulation;
        while (newPopulation.size() < populationSize) {
            Individual parent1 = select(population, fitness, rng);
            Individual parent2 = select(population, fitness, rng);

            Individual offspring = crossover(parent1, parent2, rng);
            mutate(offspring, mutationRate, rng);

            newPopulation.push_back(offspring);
        }

        population = move(newPopulation);

      auto bestIt = max_element(fitness.begin(), fitness.end());
        int bestIndex = distance(fitness.begin(), bestIt);
    }
}

int main() {
    const int populationSize = 20;
    const int permutationSize = 10;
    const int generations = 100;
    const double mutationRate = 0.6;

    runEvolutionaryAlgorithm(populationSize, permutationSize, generations, mutationRate);

    return 0;
}
