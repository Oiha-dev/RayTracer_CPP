#ifndef SPHERE_H
#define SPHERE_H
#include "hit.h"
#include "object.h"

class sphere : public object{
public:
    point3 center;
    double radius;

    sphere(const point3& c, double r, const rayTracingMaterial& mat): object(mat) {
        center = c;
        radius = r;
    }

    hitInfo hit(const ray& r) const override {

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
};

#endif //SPHERE_H
