#include "Coach.h"
#include <iostream>

void Coach::giveTips() {
    std::cout << "Drink lots of water and male sure to get enough sleep." << std::endl;
}

void Coach::evaluateGoals(const std::vector<std::string>& data) {
    // Simple evaluation for demo purposes
    if (data.size() > 5) {
        std::cout << "I'm proud of you! Keep up the good work." << std::endl;
    } else {
        std::cout << "Push harder, I know you still got this" << std::endl;
    }
}
