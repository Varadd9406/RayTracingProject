#include <iostream>
#include <cmath>
#include "color.hpp"
#include "vec3.hpp"
#include "ray.hpp"
#include "hittable.hpp"
#include "hittable_list.hpp"
#include "utility.hpp"
#include "sphere.hpp"


color ray_color(const ray& r,const hittable& world)
{
	hit_record rec;
    if (world.hit(r, 0, infinity, rec)) 
	{
        return 0.5 * (rec.normal + color(1,1,1));
    }
	vec3 unit_direction = unit_vector(r.direction());
	auto t=  0.5*(unit_direction.y()+1.0);
    return (1.0-t)*color(1.0, 1.0, 1.0) + t*color(0.5, 0.7, 1.0);
}


int main() 
{
	#ifndef ONLINE_JUDGE
		freopen("image.ppm", "w", stdout);
	#endif

    //Image

	double aspect_ratio = 16.0/9.0;
    const int image_height = 1080;
	const int image_width = image_height*aspect_ratio;
	// std::cerr<< aspect_ratio <<" "<<image_width;

	//World
	hittable_list world;
	world.add(std::make_shared<sphere>(point3(0,0,-1),0.5));
	world.add(std::make_shared<sphere>(point3(0,-100.5,-1),100));

	
	//Camera
	double viewport_height =2;
	double viewport_width = aspect_ratio*viewport_height;
	double focal_length = 1;


	point3 origin(0,0,0);
	vec3 horizontal(viewport_width,0,0);
	vec3 vertical(0,viewport_height,0);
	vec3 lower_left_corner = origin - horizontal/2 - vertical/2 - vec3(0, 0, focal_length);

    // Render
    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

	for (int j = image_height-1; j>=0;j--) {
			for (int i = 0; i < image_width; i++) {
				double u = double(i)/(image_width-1);
				double v= double(j)/(image_height-1);
				ray r(origin, lower_left_corner + u*horizontal + v*vertical - origin);
				color pixel_color = ray_color(r, world);
				write_color(pixel_color);
			}
		}
	std::cerr << "\nDone.\n";
}