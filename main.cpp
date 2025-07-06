#include "header/camera.h"
#include "header/color.h"
#include "header/sphere.h"
#include "header/triangle.h"
#include "header/vec3.h"
#include "header/world.h"


int main(int argc, char *argv[]) {

    double half = 1;
    point3 v000 = point3(-half, -half, 3 - half);  // left, bottom, back
    point3 v001 = point3(-half, -half, 3 + half);  // left, bottom, front
    point3 v010 = point3(-half, +half, 3 - half);  // left, top, back
    point3 v011 = point3(-half, +half, 3 + half);  // left, top, front
    point3 v100 = point3(+half, -half, 3 - half);  // right, bottom, back
    point3 v101 = point3(+half, -half, 3 + half);  // right, bottom, front
    point3 v110 = point3(+half, +half, 3 - half);  // right, top, back
    point3 v111 = point3(+half, +half, 3 + half);  // right, top, front

    auto red = rayTracingMaterial(color(0.9, 0.2, 0.2));

    // Front face (z = +half)
    auto t1 = std::make_shared<triangle>(v001, v101, v111, red);
    auto t2 = std::make_shared<triangle>(v001, v111, v011, red);

    // Back face (z = -half)
    auto t3 = std::make_shared<triangle>(v000, v110, v100, red);
    auto t4 = std::make_shared<triangle>(v000, v010, v110, red);

    // Left face (x = -half)
    auto t5 = std::make_shared<triangle>(v000, v011, v001, red);
    auto t6 = std::make_shared<triangle>(v000, v010, v011, red);

    // Right face (x = +half)
    auto t7 = std::make_shared<triangle>(v100, v101, v111, red);
    auto t8 = std::make_shared<triangle>(v100, v111, v110, red);

    // Top face (y = +half)
    auto t9  = std::make_shared<triangle>(v010, v011, v111, red);
    auto t10 = std::make_shared<triangle>(v010, v111, v110, red);

    // Bottom face (y = -half)
    auto t11 = std::make_shared<triangle>(v000, v100, v101, red);
    auto t12 = std::make_shared<triangle>(v000, v101, v001, red);



    auto sphere_001 = std::make_shared<sphere>(point3(2.5,  0,    2.5),   1.0, rayTracingMaterial(color(0.3, 0.8, 0.2)));
    auto sphere_002 = std::make_shared<sphere>(point3(4.5,  -1,   2),     0.7, rayTracingMaterial(color(0.2, 0.5, 0.7)));
    auto sphere_003 = std::make_shared<sphere>(point3(-0,   -0,   3),     1.3, rayTracingMaterial(color(0.9, 0.2, 0.2)));
    auto sphere_004 = std::make_shared<sphere>(point3(5.5,  -2,   2),     0.3, rayTracingMaterial(color(0.1, 0.1, 0.1)));
    auto sun        = std::make_shared<sphere>(point3(3.5,  -110, -3.5),  50,  rayTracingMaterial(color(0, 0, 0), color(1, 1, 1), 10));
    auto sphere_006 = std::make_shared<sphere>(point3(-4.5, -2,   3.5),   2,   rayTracingMaterial(color(1.0, 1.0, 1.0)));
    auto sphere_007 = std::make_shared<sphere>(point3(0.0,  0.0,  -77.5), 79.5, rayTracingMaterial(color(0.3, 0.1, 0.5)));

    world scene({
        sphere_001, sphere_002, sphere_004, sun, sphere_006, sphere_007, // no sphere_003
        t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12                 // cube triangles
    });



    camera cam;

    cam.aspect_ratio = 16.0/9;
    cam.image_width = 1920;

    cam.lookfrom = point3(3, 7, 4.7);
    cam.lookat = point3(1.4, 2.6, 2.8);
    cam.vup = vec3(-0.1, -0.3, 0.9);
    cam.vfov = 60;

    cam.maxBounceCount = 10;
    cam.rayPerPixel = 1000;

    cam.threadCount = 12;

    cam.render(scene);
}