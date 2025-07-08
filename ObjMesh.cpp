#include "header/ObjMesh.h"
#include <fstream>
#include <ostream>
#include <iostream>
#include <bits/stdc++.h>

#include "color.h"

ObjMesh::ObjMesh(string& filePath, const point3& coord, double scale, rayTracingMaterial mat): object(mat) {
    coordinates = coord;
    this->scale = scale;
    populateTriangles(filePath);
}

void ObjMesh::populateTriangles(string& filePath) {
    std::ifstream objFile;
    objFile.open(filePath);

    if (!objFile) {
        cout << "Unable to open file:" << filePath;
        exit(1);
    }

    string currentLine;

    vector<point3> listVertex;
    double maxSize = 0;
    while (getline (objFile, currentLine)) {
        if (currentLine[0] == 'v' && currentLine[1] == ' ') {
            currentLine.erase(0, 1);
            point3 currentPoint;
            std::regex pattern("\\S+");
            std::smatch match;
            for (int i = 0; i < 3; i++) {
                if (std::regex_search(currentLine, match, pattern)) {
                    int start = match.position(0);
                    int end = start + match.length(0);

                    currentPoint[i] = atof(currentLine.substr(start, end).data());
                    maxSize = max(abs(currentPoint[i]), maxSize);
                    currentLine.erase(0, end);
                }
            }
            listVertex.push_back(currentPoint);
        }

        if (currentLine[0] == 'f' && currentLine[1] == ' ') {
            point3 vertices[3];
            currentLine.erase(0, 1);
            std::regex pattern(R"(^\s*(\d+)(?:/\d*)?(?:/\d*)?)");
            std::smatch match;
            for (int i = 0; i < 3; i++) {
                if (std::regex_search(currentLine, match, pattern)) {
                    int start = match.position(0);
                    int end = start + match.length(0);

                    int currentPoint = atoi(currentLine.substr(start, end).data());
                    currentLine.erase(start, end);
                    vertices[i] = listVertex[currentPoint - 1];
                }
            }
            auto tri = make_shared<triangle>(triangle(vertices[0], vertices[1], vertices[2], material));
            triangles.push_back(tri);
        }
    }

    cout << maxSize;

    for (auto tri : triangles) {
        tri->vertices[0] = tri->vertices[0] / maxSize * scale + coordinates;
        tri->vertices[1] = tri->vertices[1] / maxSize * scale + coordinates;
        tri->vertices[2] = tri->vertices[2] / maxSize * scale + coordinates;
    }



    objFile.close();
}


hitInfo ObjMesh::hit(const ray& r) const {
    hitInfo closestTriangleHit;
    closestTriangleHit.distance = std::numeric_limits<double>::infinity();

    for (auto& tri : triangles) {
        hitInfo hit = tri->hit(r);

        if (hit.didHit == true && hit.distance < closestTriangleHit.distance) {
            closestTriangleHit = hit;
            closestTriangleHit.material = tri->material;
        }
    }

    return closestTriangleHit;
}
