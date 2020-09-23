#ifndef CV_OBJECTS_HPP
#define CV_OBJECTS_HPP

#include <vec.hpp>
#include <ray.hpp>

#include <memory>
#include <vector>

class Material;

struct hit_record
{
	vec3f p;
	vec3f normal;
	float t;
	shared_ptr<Material> mat_ptr;

	bool front_face;

	inline void set_face_normal(const ray& r, const vec3f& outward_normal)
	{
		front_face = dot(r.direction(), outward_normal) < 0;
		normal = front_face ? *const_cast<vec3f*>(&outward_normal) : -outward_normal;
	}
};

class Hittable
{
public:
	virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const = 0;
};

class Sphere : public Hittable
{
private:
	vec3f _center;
	float _radius;
	shared_ptr<Material> _mat_ptr;
public:
	Sphere()
	{
		_center = vec3f(0.0, 0.0, 0.0);
		_radius = 0.0;
	}
	Sphere(vec3f center, float radius, shared_ptr<Material> m)
		:_center(center),
		_radius(radius),
		_mat_ptr(m)
	{
		
	}
	Sphere(vec3f center, float radius)
		:_center(center),
		_radius(radius)

	{
		
	}
	virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const
	{
		vec3f oc = r.origin() - _center;
		float a = dot(r.direction(), r.direction());
		float half_b = dot(oc, r.direction());
		float c = dot(oc, oc) - _radius*_radius;
		float discriminant = half_b*half_b - a*c;
		if(discriminant > 0)
		{
			float root = sqrt(discriminant);
			float t = (-half_b - root) / a;
			if (t > t_min && t < t_max)
			{
				rec.p = r.at(t);
				rec.t = t;
				vec3f temp_normal = (rec.p - _center) / _radius;
				rec.set_face_normal(r, temp_normal);
				rec.mat_ptr = _mat_ptr;
				return true;
			}
			t = (-half_b + root) / a;
			if (t > t_min && t < t_max)
			{
				rec.p = r.at(t);
				rec.t = t;
				vec3f temp_normal = (rec.p - _center) / _radius;
				rec.set_face_normal(r, temp_normal);
				rec.mat_ptr = _mat_ptr;
				return true;
			}
		}
		return false;
	}
};

class Hittable_list : public Hittable
{
public:
	vector<shared_ptr<Hittable>> objects;

	Hittable_list() {}
	Hittable_list(shared_ptr<Hittable> obj) { add(obj);}

	void clear() { objects.clear();}
	void add(shared_ptr<Hittable> obj) { objects.push_back(obj);}

	virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const override
	{
		hit_record tmp_rec;
		bool hit = false;
		float max = t_max;

		for(const auto& obj : objects)
		{
			if(obj->hit(r, t_min, max, tmp_rec))
			{
				rec = tmp_rec;
				hit = true;
				max = tmp_rec.t;
			}
		}
		return hit;
	}
};

#endif