#ifndef COLOR_H
#define COLOR_H
#include <fstream>


#include "vec3.h"

using color = vec3;

void write_color(std::ofstream& ImageFile, const color& pixel_color) {
    int r = min(int(255.999 * double(pixel_color.x())), 255);
    int g = min(int(255.999 * double(pixel_color.y())), 255);
    int b = min(int(255.999 * double(pixel_color.z())), 255);

    ImageFile << r << ' ' << g << ' ' << b << '\n';
}

#endif //COLOR_H
