#ifndef HIT_H
#define HIT_H
#include "material.h"
#include "ray.h"
#include "vec3.h"

class hitInfo {
public:
    hitInfo(bool did_hit, float dist, const point3 &hit_point, const vec3 &norm, const rayTracingMaterial &material) {
        didHit = did_hit;
        distance = dist;
        hitPoint = hit_point;
        normal = norm;
        this->material = material;
    }

    hitInfo() {
        didHit = false;
        distance = 0;
        hitPoint = vec3();
        normal = vec3();
        material = rayTracingMaterial();
    }

    bool didHit;
    double distance;
    point3 hitPoint;
    vec3 normal;
    rayTracingMaterial material;

};

#endif //HIT_H
