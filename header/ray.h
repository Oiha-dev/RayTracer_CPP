#pragma once
#include <random>

#include "randomUtils.h"
#include "vec3.h"

class ray {
public:
    ray(point3& orig, vec3 dir) {
        origin = orig;
        direction = dir;
    }

    point3 at(double t) const {
        return origin + t * direction;
    }

    point3 origin;
    vec3 direction;
};

inline point3 randomPointOnSphere(){
    point3 res;

    double u = randomDouble(-1, 1);
    double angle = randomDouble(0, 2 * std::numbers::pi);

    res.vec[0] = sqrt(1 - u*u) * cos(angle);
    res.vec[1] = sqrt(1 - u*u) * sin(angle);
    res.vec[2] = u;

    return res;
}


inline vec3 randomHemisphereDirection(vec3& normal) {
    vec3 randomVector = randomPointOnSphere();
    if (normal.dot(randomVector) >= 0) {
        return randomVector;
    }
    return vec3(0, 0, 0) - randomVector;
}

inline vec3 randomDirection() {
    vec3 randomVector = randomPointOnSphere();
    return vec3(0, 0, 0) - randomVector;
}