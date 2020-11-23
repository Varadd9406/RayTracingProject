#ifndef HITTABLE_HPP
#define HITTABLE_HPP

#include "ray.hpp"


class material;
struct hit_record
{
    point3 p;
    vec3 normal;
    double t;
	bool front_face ;
	std::shared_ptr<material> mat_ptr;

	void set_face_normal(const ray &r, const vec3& outward_normal)
	{
		front_face  = dot(r.direction(),outward_normal)<0;
		normal = outward_normal;
		if(!front_face)
		{
			normal = -1*normal;
		}
	}
};

class hittable {
    public:
        virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const = 0;
};

#endif