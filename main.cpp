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
    return (1.0-t)*color(1.0, 1.0, 1.0) + t*color(0.5, 0.7, 1);
}



int main() 
{
	#ifndef IMAGE
		freopen("image.ppm", "w", stdout);
	#endif

    //Image

	double aspect_ratio = 16.0/9.0;
    const int image_height =720;
	const int image_width = image_height*aspect_ratio;
	const int samples_per_pixel = 50;
	const int max_depth = 20;
	// std::cerr<< aspect_ratio <<" "<<image_width;

	//World
	hittable_list world;
	auto ground_material = std::make_shared<lambertian>(color(0.5, 0.5, 0.5));
    world.add(std::make_shared<sphere>(point3(0,-1000,0), 1000, ground_material));

    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            auto choose_mat = random_double();
            point3 center(a + 0.9*random_double(), 0.2, b + 0.9*random_double());

            if ((center - point3(4, 0.2, 0)).length() > 0.9) {
                std::shared_ptr<material> sphere_material;

                if (choose_mat < 0.8) {
                    // diffuse
                    auto albedo = color::random() * color::random();
                    sphere_material = std::make_shared<lambertian>(albedo);
                    world.add(std::make_shared<sphere>(center, 0.2, sphere_material));
                } else if (choose_mat < 0.95) {
                    // metal
                    auto albedo = color::random(0.5, 1);
                    auto fuzz = random_double(0, 0.5);
                    sphere_material = std::make_shared<metal>(albedo, fuzz);
                    world.add(std::make_shared<sphere>(center, 0.2, sphere_material));
                } else {
                    // glass
                    sphere_material = std::make_shared<dielectric>(1.5);
                    world.add(std::make_shared<sphere>(center, 0.2, sphere_material));
                }
            }
        }
    }

    auto material1 = std::make_shared<dielectric>(1.5);
    world.add(std::make_shared<sphere>(point3(0, 1, 0), 1.0, material1));

    auto material2 = std::make_shared<lambertian>(color(0.4, 0.2, 0.1));
    world.add(std::make_shared<sphere>(point3(-4, 1, 0), 1.0, material2));

    auto material3 = std::make_shared<metal>(color(0.7, 0.6, 0.5), 0.0);
    world.add(std::make_shared<sphere>(point3(4, 1, 0), 1.0, material3));
	
	//Camera
	camera cam(point3(5,2,3), point3(0,0,0), vec3(0,1,0),90,aspect_ratio);


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