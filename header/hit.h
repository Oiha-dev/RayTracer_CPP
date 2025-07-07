#pragma once

#include "material.h"
#include "vec3.h"

class hitInfo {
public:
    hitInfo(bool did_hit, float dist, const point3 &hit_point, const vec3 &norm, const rayTracingMaterial &material);
    hitInfo();

    bool didHit;
    double distance;
    point3 hitPoint;
    vec3 normal;
    rayTracingMaterial material;
};