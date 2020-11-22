#ifndef UTILITY_HPP
#define UTILITY_HPP

#include<cmath>
#include<limits>
#include<memory>
#include "ray.hpp"
#include "vec3.hpp"

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

double degrees_to_radians(double degrees)
{
	return degrees*pi/180.0;
}

#endif