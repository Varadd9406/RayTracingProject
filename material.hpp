#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include "utility.hpp"
#include "ray.hpp"
#include "hittable.hpp"
#include <algorithm>

struct hit_record;


class material
{
	public:
	virtual bool scatter(const ray& r_in,const hit_record& rec,color& attenuation,ray& scattered) const =0;
};


class lambertian : public material
{
	public:
	lambertian(const color& a):albedo(a){}

	virtual bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const override 
		{
            auto scatter_direction = rec.normal + random_unit_vector();
			if (scatter_direction.near_zero())
                scatter_direction = rec.normal;
            scattered = ray(rec.p, scatter_direction);
            attenuation = albedo;
            return true;
        }
	private:
	color albedo ;
};


class metal : public material
{
    public:
	metal(const color& a,double f) : albedo(a),fuzz(std::min(1.0,f)) {}

	virtual bool scatter(
		const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered
	) const override
	{
		vec3 reflected = reflect(unit_vector(r_in.direction()), rec.normal);
		scattered = ray(rec.p, reflected+fuzz*random_in_unit_sphere());
		attenuation = albedo;
		return (dot(scattered.direction(), rec.normal) > 0);
	}

    public:
	color albedo;
	double fuzz;
};
#endif