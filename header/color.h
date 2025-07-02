#ifndef COLOR_H
#define COLOR_H
#include <fstream>


#include "vec3.h"

using color = vec3;

void write_color(std::ofstream& ImageFile, const color& pixel_color) {
    int r = 255.999 * double(pixel_color.x());
    int g = 255.999 * double(pixel_color.y());
    int b = 255.999 * double(pixel_color.z());

    ImageFile << r << ' ' << g << ' ' << b << '\n';
}

#endif //COLOR_H
