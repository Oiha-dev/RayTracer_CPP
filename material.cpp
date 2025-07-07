#include "header/material.h"

rayTracingMaterial::rayTracingMaterial(const vec3 &color, const vec3 &emission_color, double emission_strength)
    : materialColor(color),
      emissionColor(emission_color),
      emissionStrength(emission_strength) {}

rayTracingMaterial::rayTracingMaterial(const vec3 &color)
        : materialColor(color),
          emissionColor(0, 0, 0),
          emissionStrength(0) {}

rayTracingMaterial::rayTracingMaterial()
    : materialColor(vec3(0, 0, 0)),
      emissionColor(0, 0, 0),
      emissionStrength(0) {}