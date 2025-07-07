#pragma once

#include <random>

inline std::mt19937& getEngine() {
    thread_local static std::random_device rd;
    thread_local static std::mt19937 engine(rd());
    return engine;
}

inline double randomDouble(double min, double max) {
    std::uniform_real_distribution dist(min, max);
    return dist(getEngine());
}