#include <fstream>
#include <iostream>

#include "header/color.h"
#include "header/vec3.h"
#include "header/ray.h"
#include "header/hit.h"


color ray_color(const ray& r) {
    hitInfo hit = hit_sphere(point3(0,0,-1), 0.5, r);
    if (hit.distance > 0.0) {
        return color(1, 0, 0);
    }


    double unit_direction =  r.getDirection().unit_vector().y();
    double colorFilter = 1-(unit_direction+1)*0.5;
    return (1 - colorFilter) * color(0.5, 0.7, 1) + colorFilter * color(1, 1, 1);
}

int main() {

    // Image

    auto aspect_ratio = 16.0 / 9.0;
    int image_width = 400;

    int image_height = int(image_width / aspect_ratio);
    image_height = (image_height < 1) ? 1 : image_height;

    // Camera

    auto focal_length = 1.0;
    auto viewport_height = 2.0;
    auto viewport_width = viewport_height * (double(image_width)/image_height);
    auto camera_center = point3(0, 0, 0);

    // Calculate the vectors across the horizontal and down the vertical viewport edges.
    auto viewport_u = vec3(viewport_width, 0, 0);
    auto viewport_v = vec3(0, -viewport_height, 0);

    // Calculate the horizontal and vertical delta vectors from pixel to pixel.
    auto pixel_delta_u = viewport_u / image_width;
    auto pixel_delta_v = viewport_v / image_height;

    // Calculate the location of the upper left pixel.
    auto viewport_upper_left = camera_center - vec3(0, 0, focal_length) - viewport_u/2 - viewport_v/2;
    auto pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

    // Render

    std::ofstream ImageFile("image.ppm");

    ImageFile << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int i = 0; i < image_height; i++) {
        std::clog << "\rScanlines remaining: " << (image_height - i) << ' ' << std::flush;
        for (int j = 0; j < image_width; j++) {

            point3 pixel_center = pixel00_loc + (j * pixel_delta_u) + (i * pixel_delta_v);
            vec3 ray_direction = pixel_center - camera_center;
            ray r(camera_center, ray_direction);

            color pixel_color = ray_color(r);
            write_color(ImageFile, pixel_color);

        }
    }

    std::clog << "\rDone.                 \n";

    ImageFile.close();

}
