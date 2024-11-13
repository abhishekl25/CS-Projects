#include "User.h"

User::User(const std::string& name) : name(name) {}

void User::addEntry(const std::string& entry) {
    entries.push_back(entry);
}

std::vector<std::string> User::getEntries() const {
    return entries;
}
