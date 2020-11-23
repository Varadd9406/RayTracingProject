#include <iostream>
#include <cmath>
#include "vec3.hpp"
#include "ray.hpp"
#include "color.hpp"
#include "hittable.hpp"
#include "hittable_list.hpp"
#include "utility.hpp"
#include "sphere.hpp"
#include "camera.hpp"
#include "material.hpp"


color ray_color(const ray& r,const hittable& world,int depth)
{
	hit_record rec;
	if (depth <= 0) return color(0,0,0);
    if (world.hit(r,  0.001, infinity, rec)) 
	{
		ray scattered ;
		color attenuation;
		if (rec.mat_ptr->scatter(r,rec,attenuation,scattered))
		{
			return attenuation*ray_color(scattered,world,depth-1);
		}
		return color(0,0,0);
	}
	vec3 unit_direction = unit_vector(r.direction());
	double t=  0.5*(unit_direction.y()+1.0);
    return (1.0-t)*color(1.0, 1.0, 1.0) + t*color(0.5, 0.7, 1.0);
}


int main() 
{
	#ifndef IMAGE
		freopen("image.ppm", "w", stdout);
	#endif

    //Image

	double aspect_ratio = 16.0/9.0;
    const int image_height =1080;
	const int image_width = image_height*aspect_ratio;
	const int samples_per_pixel = 10;
	const int max_depth = 20;
	// std::cerr<< aspect_ratio <<" "<<image_width;

	//World
	hittable_list world;
	std::shared_ptr<lambertian> material_ground =  std::make_shared<lambertian>(color(0.8,0.8,0));
	std::shared_ptr<lambertian> material_middle =  std::make_shared<lambertian>(color(0.7, 0.3, 0.3));
	std::shared_ptr<metal> material_left =  std::make_shared<metal>(color(0.8,0.8,0.8));
	std::shared_ptr<metal> material_right =  std::make_shared<metal>(color(0.8,0.6,0.2));


 	world.add(make_shared<sphere>(point3( 0.0, -100.5, -1.0), 100.0, material_ground));
    world.add(make_shared<sphere>(point3( 0.0,    0.0, -1.0),   0.5, material_middle));
    world.add(make_shared<sphere>(point3(-1.0,    0.0, -1.0),   0.5, material_left));
    world.add(make_shared<sphere>(point3( 1.0,    0.0, -1.0),   0.5, material_right));
	
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
				pixel_color += ray_color(r, world,max_depth);
			}
			write_color(pixel_color,samples_per_pixel);
			
		}
	}
	std::cerr << "\nDone.\n";
}