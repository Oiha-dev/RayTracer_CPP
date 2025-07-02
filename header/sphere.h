#ifndef SPHERE_H
#define SPHERE_H
#include "vec3.h"

struct RayTracingMaterial {
    vec3 color;
};

struct sphere {
    vec3 position;
    double radius;
    RayTracingMaterial material;
};

#endif //SPHERE_H
