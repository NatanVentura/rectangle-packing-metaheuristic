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
        std::uniform_real_distribution<> dis;
        if (i < 5) {
            dis = std::uniform_real_distribution<>(1, 100); // Generate numbers between 1 and 10
        } else if (i < 10) {
            dis = std::uniform_real_distribution<>(1, 1000); // Generate numbers between 1 and 100
        } else if (i < 15) {
            dis = std::uniform_real_distribution<>(1, 10000); // Generate numbers between 1 and 1000
        } else {
            dis = std::uniform_real_distribution<>(1, 100000); // Generate numbers between 1 and 10000
        }

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
    std::ofstream indexFile("Data/index.txt");

    for (int count : rectangleCounts) {
        std::string dir = "Data/" + std::to_string(count);
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
