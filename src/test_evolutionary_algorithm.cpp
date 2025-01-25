#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <util.hpp>
#include <instance.hpp>
#include <simulated_annealing.hpp>
#include <evolutionary_algorithm.hpp>

void testEvolutionaryAlgorithm(const std::vector<double>& widths, const std::vector<double>& heights, const std::string& outputFile) {
    std::ofstream outFile(outputFile);

    std::vector<int> populationSizes = {10, 20, 30};
    std::vector<int> generations = {50, 100, 150};
    std::vector<double> mutationRates = {0.1, 0.3, 0.5};
    std::vector<double> crossoverRates = {0.5, 0.7, 0.9};

    for (int popSize : populationSizes) {
        for (int gen : generations) {
            for (double mutRate : mutationRates) {
                for (double crossRate : crossoverRates) {
                    auto start = std::chrono::high_resolution_clock::now();
                    EvolutionaryAlgorithm ea(widths, heights);
                    ea.initialize(popSize, gen, mutRate, crossRate);
                    Instance instance = ea.get_best_solution();
                    auto end = std::chrono::high_resolution_clock::now();
                    std::chrono::duration<double> duration = end - start;

                    outFile << "Population Size: " << popSize << ", Generations: " << gen
                            << ", Mutation Rate: " << mutRate << ", Crossover Rate: " << crossRate << std::endl;
                    outFile << "Time: " << duration.count() << " seconds" << std::endl;
                    outFile << "Area: " << instance.get_area() << std::endl;
                    outFile << std::endl;
                }
            }
        }
    }

    outFile.close();
}

void analyzeParameterImpact(const std::vector<double>& widths, const std::vector<double>& heights, const std::string& outputFile) {
    std::ofstream outFile(outputFile);

    int fixedPopulationSize = 20;
    int fixedGenerations = 100;
    double fixedMutationRate = 0.3;
    double fixedCrossoverRate = 0.7;

    // Analyze impact of population size
    std::vector<int> populationSizes = {10, 20, 30, 40, 50, 100, 200, 500, 1000};
    for (int popSize : populationSizes) {
        auto start = std::chrono::high_resolution_clock::now();
        EvolutionaryAlgorithm ea(widths, heights);
        ea.initialize(popSize, fixedGenerations, fixedMutationRate, fixedCrossoverRate);
        Instance instance = ea.get_best_solution();
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = end - start;

        outFile << "Population Size: " << popSize << ", Generations: " << fixedGenerations
                << ", Mutation Rate: " << fixedMutationRate << ", Crossover Rate: " << fixedCrossoverRate << std::endl;
        outFile << "Time: " << duration.count() << " seconds" << std::endl;
        outFile << "Area: " << instance.get_area() << std::endl;
        outFile << std::endl;
    }

    // Analyze impact of generations
    std::vector<int> generations = {50, 100, 150, 200, 300, 400, 500};
    for (int gen : generations) {
        auto start = std::chrono::high_resolution_clock::now();
        EvolutionaryAlgorithm ea(widths, heights);
        ea.initialize(fixedPopulationSize, gen, fixedMutationRate, fixedCrossoverRate);
        Instance instance = ea.get_best_solution();
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = end - start;

        outFile << "Population Size: " << fixedPopulationSize << ", Generations: " << gen
                << ", Mutation Rate: " << fixedMutationRate << ", Crossover Rate: " << fixedCrossoverRate << std::endl;
        outFile << "Time: " << duration.count() << " seconds" << std::endl;
        outFile << "Area: " << instance.get_area() << std::endl;
        outFile << std::endl;
    }

    // Analyze impact of mutation rate
    std::vector<double> mutationRates = {0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.9};
    for (double mutRate : mutationRates) {
        auto start = std::chrono::high_resolution_clock::now();
        EvolutionaryAlgorithm ea(widths, heights);
        ea.initialize(fixedPopulationSize, fixedGenerations, mutRate, fixedCrossoverRate);
        Instance instance = ea.get_best_solution();
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = end - start;

        outFile << "Population Size: " << fixedPopulationSize << ", Generations: " << fixedGenerations
                << ", Mutation Rate: " << mutRate << ", Crossover Rate: " << fixedCrossoverRate << std::endl;
        outFile << "Time: " << duration.count() << " seconds" << std::endl;
        outFile << "Area: " << instance.get_area() << std::endl;
        outFile << std::endl;
    }

    // Analyze impact of crossover rate
    std::vector<double> crossoverRates = {0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9};
    for (double crossRate : crossoverRates) {
        auto start = std::chrono::high_resolution_clock::now();
        EvolutionaryAlgorithm ea(widths, heights);
        ea.initialize(fixedPopulationSize, fixedGenerations, fixedMutationRate, crossRate);
        Instance instance = ea.get_best_solution();
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = end - start;

        outFile << "Population Size: " << fixedPopulationSize << ", Generations: " << fixedGenerations
                << ", Mutation Rate: " << fixedMutationRate << ", Crossover Rate: " << crossRate << std::endl;
        outFile << "Time: " << duration.count() << " seconds" << std::endl;
        outFile << "Area: " << instance.get_area() << std::endl;
        outFile << std::endl;
    }

    outFile.close();
}

void readInstanceFile(const std::string& inputFile, std::vector<double>& widths, std::vector<double>& heights) {
    std::ifstream inFile(inputFile);
    int numRectangles;
    inFile >> numRectangles;

    widths.resize(numRectangles);
    heights.resize(numRectangles);

    for (int i = 0; i < numRectangles; ++i) {
        inFile >> widths[i] >> heights[i];
    }

    inFile.close();
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <input_file> <output_file>" << std::endl;
        return 1;
    }

    std::string inputFile = argv[1];
    std::string outputFile = argv[2];

    std::vector<double> widths;
    std::vector<double> heights;

    readInstanceFile(inputFile, widths, heights);
    // testEvolutionaryAlgorithm(widths, heights, outputFile);

    analyzeParameterImpact(widths, heights, "parameter_impact_analysis.txt");

    std::cout << "Testing completed." << std::endl;
    return 0;
}
