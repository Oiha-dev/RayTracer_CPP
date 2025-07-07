#pragma once

#include <thread>

#include "color.h"
#include "hit.h"
#include "ray.h"
#include "world.h"

class camera {

public:
    double aspect_ratio{};
    int image_width{};
    int maxBounceCount{};
    int rayPerPixel{};
    int threadCount;
    point3 lookfrom;
    point3 lookat;
    vec3   vup;
    double vfov{};

    void render(world& world);
    void initialise();

private:
    unsigned int image_height{};
    vec3 pixel00_loc;
    vec3 pixel_delta_u;
    vec3 pixel_delta_v;
    vec3 camera_up;

    static hitInfo calculateClosestHit(const ray& r, const world& world);
    color globalIllumination(const ray& r) const ;
    color trace(ray &r, const world& world) const ;
    void calculateColorThread(int threadID, vector<color>& imageBuffer, const world& world, std::atomic<int>& completed_pixels);
};