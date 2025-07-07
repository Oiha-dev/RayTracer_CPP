#pragma once

#include "ray.h"
#include "material.h"
#include "hit.h"

class object {
public:
    rayTracingMaterial material;

    explicit object(const rayTracingMaterial& mat);

    virtual ~object() = default;

    virtual hitInfo hit(const ray& r) const = 0;
};