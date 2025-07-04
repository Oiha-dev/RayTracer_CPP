#include <fstream>
#include <iostream>

#include "header/color.h"
#include "header/vec3.h"
#include "header/ray.h"
#include "header/hit.h"
#include "header/world.h"

sphere sphere_001 = sphere(point3(2.4479193687438965,   0.056793272495269775, 2.5536842346191406), 1.0, rayTracingMaterial(color(0.3515300452709198, 0.7991039156913757, 0.20507897436618805)));
sphere sphere_002 = sphere(point3(4.336178779602051,    -0.7915282845497131, 2.131769895553589), 0.7008898854255676, rayTracingMaterial(color(0.22322599589824677, 0.46778416633605957, 0.6938720941543579)));
sphere sphere_003 = sphere(point3(-0.22510182857513428, -0.1166074275970459, 2.9572179317474365), 1.3480886220932007, rayTracingMaterial(color(0.863153, 0.238398, 0.184475)));
sphere sphere_004 = sphere(point3(5.566188335418701   , -2.099975347518921, 1.7639981508255005), 0.38122379779815674, rayTracingMaterial(color(0.010219560004770756, 0.010219560004770756, 0.010219560004770756)));
sphere sun        = sphere(point3(3.5167737007141113  , -114.72481536865234, -3.469789981842041), 50, rayTracingMaterial(color(0, 0, 0), color(1, 1, 1), 10));
sphere sphere_006 = sphere(point3(-4.518723011016846  , -1.7529833316802979, 3.2281835079193115), 2.1024038791656494, rayTracingMaterial(color(1.0, 1.0, 1.0)));
sphere sphere_007 = sphere(point3(0.0               , 0.0, -77.6045913696289), 79.64906311035156, rayTracingMaterial(color(0.3402877748012543, 0.02465110644698143, 0.4506969153881073)));


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

    point3 lookfrom = point3(2.96203351020813, 7.020042419433594, 4.710366249084473);   // Point camera is looking from
    point3 lookat   = point3(1.4069113731384277, 2.652738094329834, 2.837334632873535);  // Point camera is looking at
    vec3   vup      = vec3(-0.12566393613815308, -0.35290011763572693, 0.927183985710144);     // Camera-relative "up" direction
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

            for (int k = 0; k < rayPerPixel; k++) {
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
