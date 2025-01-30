#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <filesystem>
#include <cmath>

namespace fs = std::filesystem;

void generateInstances(int numRectangles, int numInstances, const std::string& dir) {
    std::random_device rd;
    std::mt19937 gen(rd());

    for (int i = 0; i < numInstances; ++i) {
        auto dis = std::uniform_int_distribution(1, 10000);

        std::string filename = dir + "/instance_" + std::to_string(i) + ".txt";
        std::ofstream outFile(filename);
        outFile << numRectangles << std::endl;
        for (int j = 0; j < numRectangles; ++j) {
            int64_t width = static_cast<int64_t>(dis(gen)); // Generate width
            int64_t height = static_cast<int64_t>(dis(gen)); // Generate height
            outFile << width << " " << height << std::endl;
        }
        outFile.close();
    }
}

int main() {
    std::vector<int> rectangleCounts = {16, 32, 64, 128, 256, 512};
    int numInstances = 20;
    std::ofstream indexFile("data/index.txt");

    for (int count : rectangleCounts) {
        std::string dir = "data/" + std::to_string(count);
        fs::create_directories(dir);
        generateInstances(count, numInstances, dir);

        for (int i = 0; i < numInstances; ++i) {
            indexFile << dir + "/instance_" + std::to_string(i) + ".txt" << std::endl;
        }
    }

    indexFile.close();
    std::cout << "Data generation completed." << std::endl;
    return 0;
}
