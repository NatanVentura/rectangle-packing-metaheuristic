#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <instance.hpp>

struct Module {
    std::string name;
    std::string type;
    std::vector<int64_t> dimensions;
};

std::vector<Module> readModules(const std::string& filename) {
    std::ifstream file(filename);
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
            int value;
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
            int64_t width = module.dimensions[i+3]-module.dimensions[i + 1];
            widths.push_back(width);
            heights.push_back(height);
        }
    }

    return {heights, widths};
}

// int main() {
//     std::string filename = "Data/hp.yal.txt";
//     auto modules = readModules(filename);
//     auto [heights, widths] = getHeightsAndWidths(modules);

//     std::cout << "Heights: ";
//     for (const auto& height : heights) {
//         std::cout << height << " ";
//     }
//     std::cout << std::endl;

//     std::cout << "Widths: ";
//     for (const auto& width : widths) {
//         std::cout << width << " ";
//     }
//     std::cout << std::endl;

//     return 0;
// }
