#ifndef OBJECT_H
#define OBJECT_H

#include "ray.h"
#include "material.h"

class object {
public:
    rayTracingMaterial material;

    explicit object(const rayTracingMaterial& mat) {
        this->material = mat;
    }

    virtual ~object() = default;

    virtual hitInfo hit(const ray& r) const = 0;
};

#endif // OBJECT_H
