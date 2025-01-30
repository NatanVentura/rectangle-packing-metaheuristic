#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <filesystem>
#include <chrono>
#include <util.hpp>
#include <DAG.hpp>
#include <instance.hpp>
#include <simulated_annealing.hpp>
#include <evolutionary_algorithm.hpp>

namespace fs = std::filesystem;

void processInstance(const std::string& inputFile, const std::string& outputFile) {
    std::ifstream inFile(inputFile);
    std::ofstream outFile(outputFile);

    int numRectangles;
    inFile >> numRectangles;

    std::vector<int64_t> widths(numRectangles);
    std::vector<int64_t> heights(numRectangles);

    for (int i = 0; i < numRectangles; ++i) {
        inFile >> widths[i] >> heights[i];
    }

    // Process without genetic algorithm
    auto start = std::chrono::high_resolution_clock::now();
    Instance instance(widths, heights);
    instance.gen_random_seq();

    SimulatedAnnealing sa(instance, 1);
    sa.initialize(100000, 0.99);
    sa.optimize();
    instance = sa.get_best_solution();
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;

    outFile << "Without Genetic Algorithm:" << '\n';
    outFile << "Time: " << duration.count() << " seconds" << '\n';
    outFile << "Area: " << instance.get_area() << '\n';
    outFile << "Dimensions:" << '\n';
    {
        auto [f, s] = instance.get_dimensions();
        for(int i = 0; i < f.size(); i++) {
            outFile << f[i] << ' ' << s[i] << '\n';
        }
    }
    outFile << "Coordinates:" << '\n';
    {
        auto [f, s] = instance.get_dimensions();
        for(int i = 0; i < f.size(); i++) {
            outFile << f[i] << ' ' << s[i] << '\n';
        }
    }


    // Process with genetic algorithm
    start = std::chrono::high_resolution_clock::now();
    EvolutionaryAlgorithm ea(widths, heights, 1, 50, 50, 0.7, 0.4);
    instance = ea.get_best_solution();

    sa = SimulatedAnnealing(instance, 1);
    sa.initialize(100000, 0.99);
    sa.optimize();
    instance = sa.get_best_solution();
    end = std::chrono::high_resolution_clock::now();
    duration = end - start;

    outFile << "With Genetic Algorithm:" << '\n';
    outFile << "Time: " << duration.count() << " seconds" << '\n';
    outFile << "Area: " << instance.get_area() << '\n';
    outFile << "Dimensions:" << '\n';
    outFile << "Dimensions:" << '\n';
    {
        auto [f, s] = instance.get_dimensions();
        for(int i = 0; i < f.size(); i++) {
            outFile << f[i] << ' ' << s[i] << '\n';
        }
    }
    outFile << "Coordinates:" << '\n';
    {
        auto [f, s] = instance.get_dimensions();
        for(int i = 0; i < f.size(); i++) {
            outFile << f[i] << ' ' << s[i] << '\n';
        }
    }
}

int main() {
    std::ifstream indexFile("data/index.txt");
    std::ofstream resultIndexFile("resultado/index.txt");
    std::string inputFile;

    while (std::getline(indexFile, inputFile)) {
        std::string dir = "resultado/" + inputFile.substr(5, inputFile.find('/', 5) - 5);
        fs::create_directories(dir);
        std::string outputFile = dir + "/" + inputFile.substr(inputFile.find_last_of('/') + 1);
        processInstance(inputFile, outputFile);
        resultIndexFile << outputFile << '\n';
    }

    indexFile.close();
    resultIndexFile.close();
    std::cout << "Processing completed." << '\n';
    return 0;
}
