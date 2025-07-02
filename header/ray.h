#ifndef RAY_H
#define RAY_H
#include "vec3.h"

class ray {
public:

    ray(point3& orig, vec3 dir) {
        origin = orig;
        direction = dir;
    }

    point3 getOrigin() const {
        return origin;
    }

    vec3 getDirection() const {
        return direction;
    }

    point3 at(double t) const {
        return origin + t * direction;
    }


private:
    point3 origin;
    vec3 direction;
};

#endif //RAY_H
