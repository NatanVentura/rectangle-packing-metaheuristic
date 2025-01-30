#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <filesystem>
#include <chrono>
#include "util.hpp"
#include "DAG.hpp"
#include "instance.hpp"
#include "simulated_annealing.hpp"
#include "evolutionary_algorithm.hpp"

namespace fs = std::filesystem;

struct Module {
    std::string name;
    std::string type;
    std::vector<int64_t> dimensions;
};

std::vector<Module> readModules(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return {};
    }

    std::string line;
    std::vector<Module> modules;
    Module currentModule;

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string word;
        iss >> word;

        if (word == "MODULE") {
            if (!currentModule.name.empty()) {
                modules.push_back(currentModule);
                currentModule = Module();
            }
            iss >> currentModule.name;
        } else if (word == "TYPE") {
            iss >> currentModule.type;
        } else if (word == "DIMENSIONS") {
            int64_t value;
            while (iss >> value) {
                currentModule.dimensions.push_back(value);
            }
        } else if (word == "ENDMODULE") {
            modules.push_back(currentModule);
            currentModule = Module();
        }
    }

    if (!currentModule.name.empty()) {
        modules.push_back(currentModule);
    }

    return modules;
}

std::pair<std::vector<int64_t>, std::vector<int64_t>> getHeightsAndWidths(const std::vector<Module>& modules) {
    std::vector<int64_t> heights;
    std::vector<int64_t> widths;

    for (const auto& module : modules) {
        for (size_t i = 0; i < module.dimensions.size(); i += 8) {
            int64_t height = module.dimensions[i + 2] - module.dimensions[i + 4];
            int64_t width = module.dimensions[i + 3] - module.dimensions[i + 1];
            widths.push_back(width);
            heights.push_back(height);
        }
    }

    return {heights, widths};
}

std::pair<std::vector<int64_t>, std::vector<int64_t>> readGeneratedInstance(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return {};
    }

    int numRectangles;
    file >> numRectangles;

    std::vector<int64_t> widths(numRectangles);
    std::vector<int64_t> heights(numRectangles);

    for (int i = 0; i < numRectangles; ++i) {
        file >> widths[i] >> heights[i];
    }

    return {heights, widths};
}

void processInstance(std::pair<std::vector<int64_t>, std::vector<int64_t>> modules, const std::string& outputFile) {
    auto [heights, widths] = modules;
    
    std::ofstream outFile(outputFile);

    // Debug prints
    std::cout << "Heights: ";
    for (const auto& height : heights) {
        std::cout << height << " ";
    }
    std::cout << std::endl;
    std::cout << "Widths: ";
    for (const auto& width : widths) {
        std::cout << width << " ";
    }
    std::cout <<"\n"<< std::endl;

    // Process without genetic algorithm

    auto start = std::chrono::high_resolution_clock::now();
    Instance instance(widths, heights);
    instance.gen_random_seq();
    SimulatedAnnealing sa(instance, 600);
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
    EvolutionaryAlgorithm ea(widths, heights, 600, 50, 50, 0.7, 0.4);
    instance = ea.get_best_solution();

    sa = SimulatedAnnealing(instance, 600);
    sa.initialize(100000, 0.99);
    sa.optimize();
    instance = sa.get_best_solution();
    end = std::chrono::high_resolution_clock::now();
    duration = end - start;

    outFile << "With Genetic Algorithm:" << '\n';
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
}

void processGeneratedInstances(const std::string& indexFilePath, const std::string& resultDir) {
    std::ifstream indexFile(indexFilePath);
    if (!indexFile.is_open()) {
        std::cerr << "Error: Could not open index file " << indexFilePath << std::endl;
        return;
    }

    std::string inputFile;
    while (std::getline(indexFile, inputFile)) {
        // Trim whitespace from the input file path
        inputFile.erase(0, inputFile.find_first_not_of(" \t\n\r\f\v"));
        inputFile.erase(inputFile.find_last_not_of(" \t\n\r\f\v") + 1);

        std::ifstream testFile(inputFile);
        if (!testFile.is_open()) {
            std::cerr << "Error: Could not open file listed in index: " << inputFile << std::endl;
            continue;
        }
        testFile.close();

        std::string sizeDir = resultDir + "/" + inputFile.substr(5, inputFile.find('/', 5) - 5);
        fs::create_directories(sizeDir);
        std::string outputFile = sizeDir + "/" + inputFile.substr(inputFile.find_last_of('/') + 1);
        auto modules = readGeneratedInstance(inputFile);
        if (modules.first.empty() || modules.second.empty()) {
            std::cerr << "Error: No modules read from file " << inputFile << std::endl;
            continue;
        }
        std::cout << "Processing instance: " << inputFile << std::endl;
        processInstance(modules, outputFile);
        std::cout << "here" << std::endl;
    }

    indexFile.close();
}

int main() {
    // // Process paper data
    // std::ifstream indexFile("Data/index_paper.txt");
    // if (!indexFile.is_open()) {
    //     std::cerr << "Error: Could not open index file Data/index_paper.txt" << std::endl;
    //     return 1;
    // }

    // std::ofstream resultIndexFile("resultado/index.txt");
    // std::string inputFile;

    // while (std::getline(indexFile, inputFile)) {
    //     // Trim whitespace from the input file path
    //     inputFile.erase(0, inputFile.find_first_not_of(" \t\n\r\f\v"));
    //     inputFile.erase(inputFile.find_last_not_of(" \t\n\r\f\v") + 1);

    //     std::ifstream testFile(inputFile);
    //     if (!testFile.is_open()) {
    //         std::cerr << "Error: Could not open file listed in index: " << inputFile << std::endl;
    //         continue;
    //     }
    //     testFile.close();

    //     std::string outputFile = "resultado/" + inputFile.substr(5, inputFile.find('/', 5) - 5);
    //     auto modules = readModules(inputFile);
    //     if (modules.empty()) {
    //         std::cerr << "Error: No modules read from file " << inputFile << std::endl;
    //         continue;
    //     }
    //     std::pair<std::vector<int64_t>, std::vector<int64_t>> bin = getHeightsAndWidths(modules);
    //     std::cout << "Processing instance: " << inputFile << std::endl;
    //     processInstance(bin, outputFile);
    //     resultIndexFile << outputFile << '\n';
    // }

    // indexFile.close();
    // resultIndexFile.close();

    // // Process generated data
    processGeneratedInstances("Data/index.txt", "resultado");

    std::cout << "Processing completed." << '\n';
    return 0;
}
