#include "PlayLevelData.h"
/*
int main() {
    std::vector<LevelData> levelData;

    // Read CSV file
    std::ifstream file("level_data.csv");
    if (!file.is_open()) {
        std::cerr << "Failed to open CSV file." << std::endl;
        return 1;
    }

    // Read and process each line
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        LevelData data;

        if (!(iss >> data.object >> data.positionX >> data.positionY >> data.type)) {
            std::cerr << "Failed to read CSV data from line: " << line << std::endl;
            continue;
        }

        levelData.push_back(data);
    }

    // Print loaded data
    for (const auto& data : levelData) {
        std::cout << "Object: " << data.object << ", Position: (" << data.positionX << ", " << data.positionY << "), Type: " << data.type << std::endl;
    }

    return 0;
}
*/