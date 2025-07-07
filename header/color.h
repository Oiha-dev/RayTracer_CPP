#pragma once
#include <fstream>

#include "vec3.h"

using color = vec3;

void write_color(std::ofstream& ImageFile, const color& pixel_color);
