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

    hitInfo hit(const ray& r) const override;
};

#endif //SPHERE_H
