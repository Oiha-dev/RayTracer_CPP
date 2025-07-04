#include <fstream>
#include <iostream>

#include "header/color.h"
#include "header/vec3.h"
#include "header/ray.h"
#include "header/hit.h"
#include "header/world.h"

sphere sphere_001 = sphere(point3(2.5,  0,    2.5),   1.0, rayTracingMaterial(color(0.3, 0.8, 0.2)));
sphere sphere_002 = sphere(point3(4.5,  -1,   2),     0.7, rayTracingMaterial(color(0.2, 0.5, 0.7)));
sphere sphere_003 = sphere(point3(-0,   -0,   3),     1.3, rayTracingMaterial(color(0.9, 0.2, 0.2)));
sphere sphere_004 = sphere(point3(5.5,  -2,   2),     0.3, rayTracingMaterial(color(0.1, 0.1, 0.1)));
sphere sun        = sphere(point3(3.5,  -110, -3.5),  50,  rayTracingMaterial(color(0, 0, 0), color(1, 1, 1), 10));
sphere sphere_006 = sphere(point3(-4.5, -2,   3.5),   2,   rayTracingMaterial(color(1.0, 1.0, 1.0)));
sphere sphere_007 = sphere(point3(0.0,  0.0,  -77.5), 79.5,  rayTracingMaterial(color(0.3, 0.1, 0.5)));


world world({sphere_001, sphere_002, sphere_003, sphere_004, sun, sphere_006, sphere_007});

unsigned int maxBounceCount = 10;
unsigned int rayPerPixel = 1000;


hitInfo calculateClosestHit(const ray& r) {
    hitInfo closestHit;
    closestHit.distance = std::numeric_limits<double>::infinity();

    for (sphere sphere : world.spheres) {

        hitInfo hit = hit_sphere(sphere.position, sphere.radius, r);

        if (hit.didHit == true && hit.distance < closestHit.distance) {
            closestHit = hit;
            closestHit.material = sphere.material;
        }
    }

    return closestHit;
};


color trace(ray &r) {
    color rayColor = color(1, 1, 1);
    color incomingLight = color(0, 0,0);

    for (int i = 0; i < maxBounceCount + 1; i++) {
        hitInfo hit = calculateClosestHit(r);
        if (hit.didHit) {
            r.origin = hit.hitPoint;
            r.direction = randomHemisphereDirection(hit.normal);
            vec3 emittedLight = hit.material.emissionColor * hit.material.emissionStrength;
            incomingLight += emittedLight * rayColor;
            rayColor *= hit.material.materialColor;
        } else {
            break;
        }
    }
    return incomingLight;
}

int main() {

    // Image

    auto aspect_ratio = 16.0 / 9.0;
    int image_width = 1900;

    int image_height = int(image_width / aspect_ratio);
    image_height = (image_height < 1) ? 1 : image_height;

    // Camera

    point3 lookfrom = point3(3, 7, 4.7);   // Point camera is looking from
    point3 lookat   = point3(1.4, 2.6, 2.8);  // Point camera is looking at
    vec3   vup      = vec3(-0.1, -0.3, 0.9);     // Camera-relative "up" direction
    double vfov = 60;

    double focal_length = (lookfrom - lookat).length();
    double theta = vfov * numbers::pi / 180;
    double h = std::tan(theta/2);

    auto viewport_height = 2 * h * focal_length;
    auto viewport_width = viewport_height * (double(image_width)/image_height);
    auto camera_center = lookfrom;

    vec3 w = (lookfrom - lookat).unit_vector();
    vec3 u = vup.cross(w).unit_vector();
    vec3 v = w.cross(u);

    // Calculate the vectors across the horizontal and down the vertical viewport edges.
    vec3 viewport_u = viewport_width * u;    // Vector across viewport horizontal edge
    vec3 viewport_v = viewport_height * -v;  // Vector down viewport vertical edge

    // Calculate the horizontal and vertical delta vectors from pixel to pixel.
    auto pixel_delta_u = viewport_u / image_width;
    auto pixel_delta_v = viewport_v / image_height;

    // Calculate the location of the upper left pixel.
    auto viewport_upper_left = camera_center - (focal_length * w) - viewport_u/2 - viewport_v/2;
    auto pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

    // Render

    std::ofstream ImageFile("image.ppm");

    ImageFile << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int i = 0; i < image_height; i++) {
        std::clog << "\rScanlines remaining: " << (image_height - i) << ' ' << std::flush;
        for (int j = 0; j < image_width; j++) {

            color pixel_color = color(0, 0, 0);

            point3 pixel_center = pixel00_loc + (j * pixel_delta_u) + (i * pixel_delta_v);
            vec3 ray_direction = (pixel_center - camera_center).unit_vector();

            for (int k = 0; k < rayPerPixel + 1; k++) {
                ray r(camera_center, ray_direction);
                pixel_color += trace(r);
            }
            pixel_color /= rayPerPixel;
            write_color(ImageFile, pixel_color);
        }
    }

    std::clog << "\rDone.                 \n";

    ImageFile.close();

}
