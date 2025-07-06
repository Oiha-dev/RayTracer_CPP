#ifndef MATERIAL_H
#define MATERIAL_H

#include "vec3.h"

struct rayTracingMaterial {
    vec3 materialColor;
    vec3 emissionColor;
    double emissionStrength;

    rayTracingMaterial(const vec3 &color, const vec3 &emission_color, double emission_strength)
        : materialColor(color),
          emissionColor(emission_color),
          emissionStrength(emission_strength) {}

    explicit rayTracingMaterial(const vec3 &color)
        : materialColor(color),
          emissionColor(0, 0, 0),
          emissionStrength(0) {}

    rayTracingMaterial()
        : materialColor(vec3(0, 0, 0)),
          emissionColor(0, 0, 0),
          emissionStrength(0) {}
};

#endif // MATERIAL_H
