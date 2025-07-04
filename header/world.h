#ifndef WORLD_H
#define WORLD_H
#include <list>

#include "sphere.h"


class world {
public:
    world(const list<sphere> &spheres){
        this->spheres = spheres;
        numSpheres = spheres.size();
    }

    list<sphere> spheres;
    unsigned int numSpheres;
};

#endif //WORLD_H
