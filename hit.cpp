#include "header/hit.h"

hitInfo::hitInfo(bool did_hit, float dist, const point3 &hit_point, const vec3 &norm, const rayTracingMaterial &material) {
    didHit = did_hit;
    distance = dist;
    hitPoint = hit_point;
    normal = norm;
    this->material = material;
}

hitInfo::hitInfo() {
    didHit = false;
    distance = 0;
    hitPoint = vec3();
    normal = vec3();
    material = rayTracingMaterial();
}