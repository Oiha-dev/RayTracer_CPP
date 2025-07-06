#ifndef HIT_H
#define HIT_H
#include "ray.h"
#include "object.h"
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

inline hitInfo hitSphere(const point3& center, double radius, const ray& r) {

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

// In this function we assume that the triangle coordinate are stored as ABC
inline double triangleArea(const triangle& triangle) {
    point3 AB = triangle.position[1] - triangle.position[0];
    point3 AC = triangle.position[2] - triangle.position[0];

    return AB.cross(AC).length() / 2;
}

inline bool isPointInTriangle(const triangle& ABC, const point3& point) {

    triangle ABD = ABC;
    ABD.position[2] = point;

    triangle ADC = ABC;
    ADC.position[1] = point;

    triangle DBC = ABC;
    DBC.position[0] = point;

    double areaABC = triangleArea(ABC);
    double areaABD = triangleArea(ABD);
    double areaADC = triangleArea(ADC);
    double areaDBC = triangleArea(DBC);



    return fabs(areaABC - (areaABD + areaADC + areaDBC)) < 1e-6;
}

// In this function we assume that the triangle coordinate are stored as ABC, and the hit point is D
inline hitInfo hitTriangle(triangle& ABC, const ray& r) {

    hitInfo hit;

    double divisor = ABC.normal.unit_vector().dot(r.direction.unit_vector());

    if (divisor != 0) {

        double d = ABC.normal.dot(ABC.position[0]);
        double dividend = d - ABC.normal.dot(r.origin);

        double distance = dividend/divisor;

        if (distance > 0) {

            point3 hitPlan = r.at(distance);

            if (isPointInTriangle(ABC, hitPlan)) {

                hit.didHit = true;
                hit.distance = distance;
                hit.hitPoint = hitPlan;
                hit.normal = ABC.normal.unit_vector();

            }
        }
    }

    return hit;
}



#endif //HIT_H
