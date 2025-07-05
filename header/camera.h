#ifndef CAMERA_H
#define CAMERA_H

#include <fstream>
#include <iostream>

#include "color.h"
#include "hit.h"
#include "ray.h"
#include "world.h"


class camera {

public:
    double aspect_ratio{};
    unsigned int image_width{};
    unsigned int maxBounceCount{};
    unsigned int rayPerPixel{};
    point3 lookfrom;
    point3 lookat;
    vec3   vup;
    double vfov{};

    void render(world& world) {
        initialise();

        // Render
        std::ofstream ImageFile("image.ppm");

        ImageFile << "P3\n" << image_width << ' ' << image_height << "\n255\n";

        for (int i = 0; i < image_height; i++) {
            std::clog << "\rScanlines remaining: " << (image_height - i) << ' ' << std::flush;
            for (int j = 0; j < image_width; j++) {

                color pixel_color = color(0, 0, 0);

                point3 pixel_center = pixel00_loc + (j * pixel_delta_u) + (i * pixel_delta_v);
                vec3 ray_direction = (pixel_center - lookfrom).unit_vector();

                for (int k = 0; k < rayPerPixel + 1; k++) {
                    ray r(lookfrom, ray_direction);
                    pixel_color += trace(r, world);
                }
                pixel_color /= rayPerPixel;
                write_color(ImageFile, pixel_color);
            }
        }

        std::clog << "\rDone.                 \n";

        ImageFile.close();
    }

    void initialise() {
        this->image_height = int(image_width / aspect_ratio);
        image_height = (image_height < 1) ? 1 : image_height;


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
        this->pixel_delta_u = viewport_u / image_width;
        this->pixel_delta_v = viewport_v / image_height;

        // Calculate the location of the upper left pixel.
        auto viewport_upper_left = camera_center - (focal_length * w) - viewport_u/2 - viewport_v/2;
        this->pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);
    }


private:
    unsigned int image_height{};
    vec3 pixel00_loc;
    vec3 pixel_delta_u;
    vec3 pixel_delta_v;

    static hitInfo calculateClosestHit(const ray& r, const world& world) {
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

    color trace(ray &r, const world& world) const {
        color rayColor = color(1, 1, 1);
        color incomingLight = color(0, 0,0);

        for (int i = 0; i < maxBounceCount + 1; i++) {
            hitInfo hit = calculateClosestHit(r, world);
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
};

#endif //CAMERA_H
