#include "header/OneSidedReflectiveTriangle.h"

OneSidedReflectiveTriangle::OneSidedReflectiveTriangle(const point3& a, const point3& b, const point3& c, const rayTracingMaterial& mat)
: triangle(a, b, c, mat){
}

// In this function we assume that the triangle coordinate are stored as ABC, and the hit point is D
hitInfo OneSidedReflectiveTriangle::hit(const ray& r) const {

    hitInfo hit;

    double divisor = normal.unit_vector().dot(r.direction.unit_vector());

    if (divisor >= 0) {
        return hit; // didHit remains false
    }

    if (divisor != 0) {

        double d = normal.dot(vertices[0]);
        double dividend = d - normal.dot(r.origin);

        double distance = dividend/divisor;

        if (distance > 0) {

            point3 hitPlan = r.at(distance);

            if (isPointInTriangle(hitPlan)) {
                hit.didHit = true;
                hit.distance = distance;
                hit.hitPoint = hitPlan;
                hit.normal = normal.unit_vector();
            }
        }
    }

    return hit;
}