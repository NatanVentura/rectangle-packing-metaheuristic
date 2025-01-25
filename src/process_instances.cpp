#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <filesystem>
#include <chrono>
#include <util.hpp>
#include <directed_acyclic_graph.hpp>
#include <instance.hpp>
#include <simulated_annealing.hpp>
#include <evolutionary_algorithm.hpp>

namespace fs = std::filesystem;

void processInstance(const std::string& inputFile, const std::string& outputFile) {
    std::ifstream inFile(inputFile);
    std::ofstream outFile(outputFile);

    int numRectangles;
    inFile >> numRectangles;

    std::vector<double> widths(numRectangles);
    std::vector<double> heights(numRectangles);

    for (int i = 0; i < numRectangles; ++i) {
        inFile >> widths[i] >> heights[i];
    }

    // Process without genetic algorithm
    auto start = std::chrono::high_resolution_clock::now();
    Instance instance(widths, heights);
    SimulatedAnnealing sa(instance);
    sa.initialize(100000, 0.99);
    sa.optimize();
    instance = sa.get_best_solution();
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;

    outFile << "Without Genetic Algorithm:" << std::endl;
    outFile << "Time: " << duration.count() << " seconds" << std::endl;
    outFile << "Area: " << instance.get_area() << std::endl;
    outFile << "Dimensions:" << std::endl;
    for (auto c : instance.get_dimensions()) {
        outFile << c.f << " " << c.s << std::endl;
    }
    outFile << "Coordinates:" << std::endl;
    for (auto c : instance.get_coords()) {
        outFile << c.f << " " << c.s << std::endl;
    }

    // Process with genetic algorithm
    start = std::chrono::high_resolution_clock::now();
    EvolutionaryAlgorithm ea(widths, heights);
    ea.initialize(27, 100, 0.6, 0.4);
    instance = ea.get_best_solution();

    sa = SimulatedAnnealing(instance);
    sa.initialize(100000, 0.99);
    sa.optimize();
    instance = sa.get_best_solution();
    end = std::chrono::high_resolution_clock::now();
    duration = end - start;

    outFile << "With Genetic Algorithm:" << std::endl;
    outFile << "Time: " << duration.count() << " seconds" << std::endl;
    outFile << "Area: " << instance.get_area() << std::endl;
    outFile << "Dimensions:" << std::endl;
    for (auto c : instance.get_dimensions()) {
        outFile << c.f << " " << c.s << std::endl;
    }
    outFile << "Coordinates:" << std::endl;
    for (auto c : instance.get_coords()) {
        outFile << c.f << " " << c.s << std::endl;
    }

    inFile.close();
    outFile.close();
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
        resultIndexFile << outputFile << std::endl;
    }

    indexFile.close();
    resultIndexFile.close();
    std::cout << "Processing completed." << std::endl;
    return 0;
}
