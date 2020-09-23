#ifndef CV_MATERIAL_HPP
#define CV_MATERIAL_HPP

#include <vec.hpp>

class Material
{
public:
	virtual bool scatter(
		const ray& r_in, const hit_record& rec, rgbf& attenuation, ray& scattered
	) const = 0;
};

class Lambertian : public Material
{
public:
	rgbf albedo;
	Lambertian(const rgbf& c) : albedo(c) {}
	virtual bool scatter(const ray& r_in, const hit_record& rec, rgbf& attenuation, ray& scattered) const override
	{
		vec3f direction = rec.normal + random3f_unit_vector();
		scattered = ray(rec.p, direction);
		attenuation = albedo;
		return true;
	}
};

class Metal : public Material
{
public:
	rgbf albedo;
	float fuzz;
	Metal(const rgbf& c, float fuzz) : albedo(c), fuzz(fuzz) {}
	virtual bool scatter(const ray& r_in, const hit_record& rec, rgbf& attenuation, ray& scattered) const override
	{
		vec3f direction = reflect(r_in.direction().normalize(), rec.normal);
		scattered = ray(rec.p, direction + fuzz * random3f_unit_vector());
		attenuation = albedo;
		return (dot(scattered.direction(), rec.normal) > 0);
	}
};

float schlick(float cosine, float ref_idx)
{
	auto r0 = (1-ref_idx) / (1+ref_idx);
	r0 = r0*r0;
	return r0 + (1-r0)*pow((1 - cosine),5);
}

class Dielectric : public Material
{
public:
	float ref_idx;
	Dielectric(float ref_idx) : ref_idx(ref_idx) {}
	virtual bool scatter(const ray& r_in, const hit_record& rec, rgbf& attenuation, ray& scattered) const override
	{
		attenuation = rgbf(1, 1, 1); //white
		float etai_over_etat = rec.front_face ? (1.0 / ref_idx) : ref_idx;
		vec3f unit_direction = r_in.direction().normalize();
		float cos_theta = fmin(dot(-unit_direction, rec.normal), 1.0);
		float sin_theta = sqrt(1.0 - cos_theta*cos_theta);
		if(sin_theta * etai_over_etat > 1.0)
		{
			vec3f direction = reflect(r_in.direction().normalize(), rec.normal);
			scattered = ray(rec.p, direction + random3f_unit_vector());
			return true;
		}
		else
		{
			float reflect_prob = schlick(cos_theta, etai_over_etat);
			if(random_float() < reflect_prob)
			{
				vec3f direction = reflect(r_in.direction().normalize(), rec.normal);
				scattered = ray(rec.p, direction + random3f_unit_vector());
				return true;
			}
			vec3f refracted = refract(unit_direction, rec.normal, etai_over_etat);
			scattered = ray(rec.p, refracted);
			return true;
		}
	}
};

#endif