#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "utility.hpp"

class camera
{
public:
    camera(point3 lookfrom,point3 lookat,vec3 vup,double vfov,double aspect_ratio,double aperture,double focus_dist)
		{
			double theta = degrees_to_radians(vfov);
			double h = tan(theta/2);
			double viewport_height = 2.0*h;
			auto viewport_width = aspect_ratio * viewport_height;

			vec3 w = unit_vector(lookfrom-lookat);
			vec3 u = unit_vector(cross(vup,w));
			vec3 v = cross(w,u);

			origin = lookfrom;
            horizontal = viewport_width * u;
            vertical = viewport_height * v;
            lower_left_corner = origin - horizontal/2 - vertical/2 - w;

		}

	ray get_ray(double s, double t) const {
            vec3 rd = lens_radius * random_in_unit_disk();
            vec3 offset = u * rd.x() + v * rd.y();

            return ray(
                origin + offset,
                lower_left_corner + s*horizontal + t*vertical - origin - offset
            );
        }


private:
	point3 origin;
	point3 lower_left_corner;
	vec3 horizontal;
	vec3 vertical;
    vec3 u, v, w;
    double lens_radius;

};
#endif