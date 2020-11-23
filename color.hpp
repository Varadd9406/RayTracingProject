#ifndef COLOR_HPP
#define COLOR_HPP

#include "vec3.hpp"
#include "utility.hpp"
#include <iostream>



void write_color(color pixel_color,int samples_per_pixel)
{
	double r = pixel_color.x();
    double g = pixel_color.y();
    double b = pixel_color.z();

    // Divide the color by the number of samples.
    auto scale = 1.0 / samples_per_pixel;
    r = sqrt(r*scale);
    g = sqrt(g*scale);
    b = sqrt(b*scale);

    std::cout << static_cast<int>(255.999 *  clamp(r, 0.0, 0.999)) << ' '
        << static_cast<int>(255.999 *  clamp(g, 0.0, 0.999)) << ' '
        << static_cast<int>(255.999 *  clamp(b, 0.0, 0.999)) << '\n';
}

#endif