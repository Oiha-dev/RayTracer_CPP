#ifndef TRIANGLE_H
#define TRIANGLE_H
#include "hit.h"
#include "object.h"

class triangle : public object {
public:
    point3 vertices[3];
    vec3 normal;

    triangle(const point3& a, const point3& b, const point3& c, const rayTracingMaterial& mat);
    hitInfo hit(const ray& r) const override;

private:
    
    static double triangleArea(const point3& a, const point3& b, const point3& c);
    bool isPointInTriangle(const point3& point) const;

};

#endif //TRIANGLE_H
