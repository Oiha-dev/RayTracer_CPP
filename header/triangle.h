#ifndef TRIANGLE_H
#define TRIANGLE_H
#include "hit.h"
#include "object.h"

class triangle : public object {
public:
    point3 vertices[3];
    vec3 normal;

    triangle(const point3& a, const point3& b, const point3& c, const rayTracingMaterial& mat)
    : object(mat){
        vertices[0] = a;
        vertices[1] = b;
        vertices[2] = c;
        normal = (b - a).cross(c - a).unit_vector();
    }


    // In this function we assume that the triangle coordinate are stored as ABC, and the hit point is D
    hitInfo hit(const ray& r) const override {

        hitInfo hit;

        double divisor = normal.unit_vector().dot(r.direction.unit_vector());

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


private:
    static double triangleArea(const point3& a, const point3& b, const point3& c) {
        point3 AB = b - a;
        point3 AC = c - a;

        return AB.cross(AC).length() / 2;
    }


    bool isPointInTriangle(const point3& point) const {
        double totalArea = triangleArea(vertices[0], vertices[1], vertices[2]);
        double area1 = triangleArea(point, vertices[0], vertices[1]);
        double area2 = triangleArea(point, vertices[1], vertices[2]);
        double area3 = triangleArea(point, vertices[2], vertices[0]);

        return fabs(totalArea - (area1 + area2 + area3)) < 1e-6;
    }

};

#endif //TRIANGLE_H
