#pragma once

#include "hit.h"
#include "object.h"
#include "triangle.h"

class OneSidedReflectiveTriangle : public triangle {
public:

    OneSidedReflectiveTriangle(const point3& a, const point3& b, const point3& c, const rayTracingMaterial& mat);
    hitInfo hit(const ray& r) const override;

};
