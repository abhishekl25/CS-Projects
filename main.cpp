#include <iostream>
#include "DataManager.h"
#include "User.h"
#include "Visualization.h"
#include "Coach.h"

int main() {
    DataManager dataManager("data/user_data.csv");
    User user("John Doe");

    user.addEntry("Steps: 10000, Calories: 2000, Weight: 70kg, Water: 2L");
    user.addEntry("Steps: 8000, Calories: 1800, Weight: 70kg, Water: 2.5L");

    std::vector<std::string> entries = user.getEntries();
    dataManager.saveData(entries);

    std::vector<std::string> loadedData = dataManager.loadData();
    Visualization viz;
    viz.displayData(loadedData);

    Coach coach;
    coach.giveTips();
    coach.evaluateGoals(loadedData);

    return 0;
}
