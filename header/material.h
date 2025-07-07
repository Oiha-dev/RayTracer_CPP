#pragma once

#include "vec3.h"

class rayTracingMaterial {
public:
    vec3 materialColor;
    vec3 emissionColor;
    double emissionStrength;

    rayTracingMaterial(const vec3 &color, const vec3 &emission_color, double emission_strength);
    explicit rayTracingMaterial(const vec3 &color);
    rayTracingMaterial();
};