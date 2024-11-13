#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <string>
#include <vector>

class DataManager {
public:
    DataManager(const std::string& filename);
    void saveData(const std::vector<std::string>& data);
    std::vector<std::string> loadData();
private:
    std::string filename;
};

#endif
