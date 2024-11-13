#include "DataManager.h"
#include <fstream>
#include <sstream>

DataManager::DataManager(const std::string& filename) : filename(filename) {}

void DataManager::saveData(const std::vector<std::string>& data) {
    std::ofstream file(filename);
    for (const auto& line : data) {
        file << line << std::endl;
    }
    file.close();
}

std::vector<std::string> DataManager::loadData() {
    std::vector<std::string> data;
    std::ifstream file(filename);
    std::string line;
    while (std::getline(file, line)) {
        data.push_back(line);
    }
    file.close();
    return data;
}
