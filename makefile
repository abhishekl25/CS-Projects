CXX = g++
CXXFLAGS = -std=c++17 -Wall -O2

TARGET = fitness_tracker

all: $(TARGET)

$(TARGET): src/main.cpp src/DataManager.cpp src/User.cpp src/Visualization.cpp src/Coach.cpp
    $(CXX) $(CXXFLAGS) -o $(TARGET) $^

clean:
    rm -f $(TARGET)
