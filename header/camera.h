#ifndef CAMERA_H
#define CAMERA_H

#include <fstream>
#include <iostream>
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

    void render(world& world) {
        std::clog << "Starting render..." << std::endl;

        initialise();

        auto start_time = std::chrono::high_resolution_clock::now();

        // Render
        std::ofstream ImageFile("image.ppm");

        ImageFile << "P3\n" << image_width << ' ' << image_height << "\n255\n";

        vector<color> imageBuffer(image_width * image_height);
        std::vector<std::thread> threads;

        int total_pixels = image_width * image_height;

        std::clog << "Rendering " << total_pixels << " pixels with " << threadCount << " threads..." << std::endl;

        std::atomic<int> completedPixels = 0;

        for (int i = 0; i < threadCount; ++i) {
            threads.emplace_back(&camera::calculateColorThread, this, i, std::ref(imageBuffer), std::ref(world), std::ref(completedPixels));
        }

        for (auto& t : threads) {
            t.join();
        }

        for (vec3 pixel : imageBuffer) {
            write_color(ImageFile, pixel);
        }

        ImageFile.close();

        auto end_time = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::high_resolution_clock::now() - start_time;

        auto ms_total = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
        auto minutes = ms_total / 60000;
        auto seconds = (ms_total % 60000) / 1000;
        auto milliseconds = ms_total % 1000;

        std::clog << "\rDone in " << minutes << "m " << seconds << "s " << milliseconds << "ms.             \n";


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

        this->camera_up = v;

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
    vec3 camera_up;

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

    color globalIllumination(const ray& r) const {
        double alignment = r.direction.unit_vector().dot(camera_up);
        double t = 0.5 * (alignment + 1.0);

        color top = color(0.5, 0.7, 1.0);   // Sky
        color bottom = color(1.0, 1.0, 1.0); // Horizon

        return (1.0 - t) * bottom + t * top;
    }


    color trace(ray &r, const world& world) const {
        color rayColor = color(1, 1, 1);
        color incomingLight = color(0, 0,0);

        for (int i = 0; i < maxBounceCount + 1; i++) {
            hitInfo hit = calculateClosestHit(r, world);
            if (hit.didHit) {
                r.origin = hit.hitPoint;
                r.direction = randomHemisphereDirection(hit.normal);
                //r.direction = (hit.normal + randomDirection()).unit_vector();
                vec3 emittedLight = hit.material.emissionColor * hit.material.emissionStrength;
                incomingLight += emittedLight * rayColor;
                rayColor *= hit.material.materialColor;
            } else {
                incomingLight += globalIllumination(r) * rayColor;
                break;
            }
        }
        return incomingLight;
    }

    void calculateColorThread(int threadID, vector<color>& imageBuffer, const world& world, std::atomic<int>& completed_pixels) {
        for (int k = threadID; k < imageBuffer.size(); k += threadCount) {
            color pixel_color = color(0, 0, 0);

            int i = k % image_width;
            int j = k / image_width;


            point3 pixel_center = pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
            vec3 ray_direction = (pixel_center - lookfrom).unit_vector();

            for (int l = 0; l < rayPerPixel + 1; l++) {
                ray r(lookfrom, ray_direction);
                pixel_color += trace(r, world);
            }
            pixel_color /= rayPerPixel;
            imageBuffer[k] = pixel_color;

            completed_pixels.fetch_add(1, std::memory_order_relaxed);

            if (threadID == 1) {
                int progress = 100.0 * completed_pixels / (image_width * image_height);
                clog << "\rProgress: " << progress << "%" << std::flush;
            }
        }
    }
};

#endif //CAMERA_H