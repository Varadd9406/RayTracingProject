#include <iostream>
#include <cmath>
#include "color.hpp"
#include "vec3.hpp"
#include "ray.hpp"
#include "hittable.hpp"
#include "hittable_list.hpp"
#include "utility.hpp"
#include "sphere.hpp"
#include "camera.hpp"

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
    const int image_height = 720;
	const int image_width = image_height*aspect_ratio;
	const int samples_per_pixel = 20;
	// std::cerr<< aspect_ratio <<" "<<image_width;

	//World
	hittable_list world;
	world.add(std::make_shared<sphere>(point3(0,0,-1),0.5));
	
	world.add(std::make_shared<sphere>(point3(0,-100.5,-1),100));

	
	//Camera
	camera cam;


    // Render
    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

	for (int j = image_height-1; j>=0;j--)
	{
		for (int i = 0; i < image_width; i++)
		{
			color pixel_color(0,0,0);
			for (int s = 0;s<samples_per_pixel;s++)
			{
				double u = double(i+random_double())/(image_width-1);
				double v = double(j+random_double())/(image_height-1);
				ray r = cam.get_ray(u, v);
				pixel_color += ray_color(r, world);
			}
			write_color(pixel_color,samples_per_pixel);
			
		}
		}
	std::cerr << "\nDone.\n";
}