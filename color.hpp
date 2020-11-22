#ifndef COLOR_H
#define COLOR_H

#include "vec3.hpp"

#include <iostream>



void write_color(color pixel_color) {
    std::cout << static_cast<int>(255.999 * pixel_color.x()) << ' '
        << static_cast<int>(255.999 * pixel_color.y()) << ' '
        << static_cast<int>(255.999 * pixel_color.z()) << '\n';
}

#endif