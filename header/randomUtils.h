#ifndef RANDOMUTILS_H
#define RANDOMUTILS_H

#include <random>

inline std::mt19937& getEngine() {
    static std::random_device rd;
    static std::mt19937 engine(rd());
    return engine;
}

inline double randomDouble(double min, double max) {
    std::uniform_real_distribution dist(min, max);
    return dist(getEngine());
}

#endif // RANDOMUTILS_H
