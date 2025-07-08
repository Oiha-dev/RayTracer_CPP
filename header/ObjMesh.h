#pragma once
#include <memory>
#include <vector>

#include "triangle.h"


class ObjMesh : public object{
public:
    std::vector<shared_ptr<triangle>> triangles;
    point3 coordinates;
    double scale;

    ObjMesh(string& filePath, const point3& coordinates, double scale, rayTracingMaterial mat);
    hitInfo hit(const ray& r) const override;

private:
    void populateTriangles(string& filePath);

};
