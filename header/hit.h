#ifndef HIT_H
#define HIT_H
#include "ray.h"
#include "vec3.h"

class hitInfo {
public:
    hitInfo(bool did_hit, float dist, const point3 &hit_point, const vec3 &norm) {
        didHit = did_hit;
        distance = dist;
        hitPoint = hit_point;
        normal = norm;
    }

    hitInfo() {
        didHit = false;
        distance = 0;
        hitPoint = vec3();
        normal = vec3();
    }

    bool didHit;
    double distance;
    point3 hitPoint;
    vec3 normal;

};

inline hitInfo hit_sphere(const point3& center, double radius, const ray& r) {

    hitInfo hit;

    vec3 rayPos = r.getOrigin() - center;
    vec3 rayDir = r.getDirection().unit_vector();

    double result = rayPos.dot(rayDir) * rayPos.dot(r.getDirection()) - (rayPos.dot(rayPos) - radius * radius);

    if (result >= 0) {

        double distance = min(-rayPos.dot(rayDir) + sqrt(result), -rayPos.dot(rayDir) - sqrt(result));

        if (distance >= 0) {
            hit.didHit = true;
            hit.distance = distance;
            hit.hitPoint = r.at(distance);
            hit.normal = (hit.hitPoint - center).unit_vector();
        }
    }
    return hit;
}

#endif //HIT_H
