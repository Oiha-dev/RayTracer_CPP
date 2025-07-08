#include "ObjMesh.h"
#include "header/camera.h"
#include "header/color.h"
#include "header/sphere.h"
#include "header/triangle.h"
#include "header/vec3.h"
#include "header/world.h"


int main(int argc, char *argv[]) {


    string filename = "mesh/suzanne.obj";
    auto Cube = std::make_shared<ObjMesh>(ObjMesh(filename, point3(0,  0,   3.2), 1, rayTracingMaterial(color(0.9, 0.2, 0.2))));

    auto sphere_001 = std::make_shared<sphere>(point3(2.5,  0,    2.5),   1.0, rayTracingMaterial(color(0.3, 0.8, 0.2)));
    auto sphere_002 = std::make_shared<sphere>(point3(4.5,  -1,   2),     0.7, rayTracingMaterial(color(0.2, 0.5, 0.7)));
    auto sphere_003 = std::make_shared<sphere>(point3(-0,   -0,   3),     1.3, rayTracingMaterial(color(0.9, 0.2, 0.2)));
    auto sphere_004 = std::make_shared<sphere>(point3(5.5,  -2,   2),     0.3, rayTracingMaterial(color(0.1, 0.1, 0.1)));
    auto sun        = std::make_shared<sphere>(point3(3.5,  -110, -3.5),  50,  rayTracingMaterial(color(0, 0, 0), color(1, 1, 1), 10));
    auto sphere_006 = std::make_shared<sphere>(point3(-4.5, -2,   3.5),   2,   rayTracingMaterial(color(1.0, 1.0, 1.0)));
    auto sphere_007 = std::make_shared<sphere>(point3(0.0,  0.0,  -77.5), 79.5, rayTracingMaterial(color(0.3, 0.1, 0.5)));

    world scene({
        sphere_001, sphere_002, sphere_004, sun, sphere_006, sphere_007, Cube
    });



    camera cam;

    cam.aspect_ratio = 16.0/9;
    cam.image_width = 1920;

    cam.lookfrom = point3(3, 7, 4.7);
    cam.lookat = point3(1.4, 2.6, 2.8);
    cam.vup = vec3(-0.1, -0.3, 0.9);
    cam.vfov = 60;

    cam.maxBounceCount = 10;
    cam.rayPerPixel = 100;

    cam.threadCount = 12;

    cam.render(scene);
}