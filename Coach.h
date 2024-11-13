#ifndef COACH_H
#define COACH_H

#include <string>
#include <vector>

class Coach {
public:
    void giveTips();
    void evaluateGoals(const std::vector<std::string>& data);
};

#endif
