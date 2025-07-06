#ifndef SPHERE_H
#define SPHERE_H
#include "vec3.h"

struct rayTracingMaterial {
    rayTracingMaterial(const vec3 &color, const vec3 &emission_color, double emission_strength)
        : materialColor(color),
          emissionColor(emission_color),
          emissionStrength(emission_strength) {
    }

    explicit rayTracingMaterial(const vec3 &color)
    : materialColor(color),
      emissionColor(0, 0, 0),
      emissionStrength(0) {
    }

    explicit rayTracingMaterial()
    : materialColor(color(0, 0, 0)),
      emissionColor(0, 0, 0),
      emissionStrength(0) {
    }

    vec3 materialColor;
    vec3 emissionColor;
    double emissionStrength;
};

struct sphere {
    vec3 position;
    double radius;
    rayTracingMaterial material;
};

struct triangle {

    vec3 position[3];
    vec3 normal;
    rayTracingMaterial material;
};

#endif //SPHERE_H
