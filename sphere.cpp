#include "header/sphere.h"

hitInfo sphere::hit(const ray& r) const {
    hitInfo hit;

    vec3 rayPos = r.origin - center;
    vec3 rayDir = r.direction.unit_vector();

    double result = rayPos.dot(rayDir) * rayPos.dot(rayDir) - (rayPos.dot(rayPos) - radius * radius);

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