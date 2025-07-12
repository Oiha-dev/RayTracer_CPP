#include "ObjMesh.h"
#include "OneSidedReflectiveTriangle.h"
#include "header/camera.h"
#include "header/color.h"
#include "header/sphere.h"
#include "header/vec3.h"
#include "header/world.h"

#include "header/CLI11.hpp"

int main(int argc, char *argv[]) {
    CLI::App app{"Ray Tracer CLI Configuration"};

    int image_width = 400;
    int max_bounce_count = 10;
    int rays_per_pixel = 100;
    int thread_count = 12;

    app.add_option("--image-width", image_width, "Width of the output image (pixels)")->check(CLI::PositiveNumber);
    app.add_option("--max-bounce", max_bounce_count, "Maximum number of ray bounces")->check(CLI::PositiveNumber);
    app.add_option("--ray-per-pixel", rays_per_pixel, "Number of rays per pixel for sampling")->check(CLI::PositiveNumber);
    app.add_option("--threads", thread_count, "Number of threads to use for rendering")->check(CLI::PositiveNumber);

    CLI11_PARSE(app, argc, argv);

    // Scene objects
    string frogBodyFileName = "mesh/frogBody.obj";
    auto frogBody = std::make_shared<ObjMesh>(ObjMesh(frogBodyFileName, point3(0.0, 0.0, 0.0), 1.0, rayTracingMaterial(color(0.3, 0.5, 0.1))));
    string frogFaceFileName = "mesh/frogFace.obj";
    auto frogFace = std::make_shared<ObjMesh>(ObjMesh(frogFaceFileName, point3(0.0, 0.0, 0.0), 1.0, rayTracingMaterial(color(0.0, 0.0, 0.0))));

    world scene({
        frogBody, frogFace
    });

    camera cam;

    cam.aspect_ratio = 16.0 / 9.0;
    cam.image_width = image_width;

    cam.lookfrom = point3(7.4, -6.9, 5.0);
    cam.lookat = point3(0, 0, 0);
    cam.vup = vec3(-0.3, 0.3, 0.9);
    cam.vfov = 20;

    cam.maxBounceCount = max_bounce_count;
    cam.rayPerPixel = rays_per_pixel;
    cam.threadCount = thread_count;

    cam.render(scene);
}