#include <defines.hpp>
#include <vec.hpp>
#include <img.hpp>
#include <ray.hpp>
#include <objects.hpp>
#include <camera_old.hpp>
#include <color.hpp>
#include <material.hpp>

rgbf ray_color(const ray& r, const Hittable_list& world, int depth) {
	if(depth <= 0) return rgbf(0, 0, 0);
	hit_record rec;
	vec3f unit_direction = r.direction().normalize();
	if(world.hit(r, 0.001, infinity, rec))
	{
		ray scattered;
		rgbf attenuation;
		if(rec.mat_ptr->scatter(r, rec, attenuation, scattered))
		{
			return attenuation * ray_color(scattered, world, depth - 1);
		}
		return rgbf(0, 0, 0);
	}
	unit_direction = r.direction().normalize();
	float t = 0.5*(unit_direction.y() + 1.0);
	return (1.0-t)*rgbf(1.0, 1.0, 1.0) + t*rgbf(0.5, 0.7, 1.0);
}

int main()
{
	const auto aspect_ratio = 16.0 / 9.0;
	const int image_width = 400;
	const int image_height = static_cast<int>(image_width / aspect_ratio);
	const int samples_per_pixel = 100;
	const int max_depth = 50;

	auto material_ground = make_shared<Lambertian>(rgbf(0.8, 0.8, 0.0));
	auto material_center = make_shared<Lambertian>(rgbf(0.7, 0.3, 0.3));
	auto material_left   = make_shared<Dielectric>(1.5);
	auto material_right  = make_shared<Metal>(rgbf(0.8, 0.6, 0.2), 0.6);

	Hittable_list world;
	world.add(make_shared<Sphere>(vec3f(0, 0, -1), 0.5, material_center));
	world.add(make_shared<Sphere>(vec3f(0, -100.5, -1), 100, material_ground));
	world.add(make_shared<Sphere>(vec3f(-1.0, 0.0, -1.0), 0.5, material_left));
	world.add(make_shared<Sphere>(vec3f( 1.0, 0.0, -1.0), 0.5, material_right));

	Camera cam;

	Img pic(image_width, image_height);
	for(int i = 0; i < image_width; i++)
	{
		for(int j = 0; j < image_height; j++)
		{
			rgbf tmpc(0, 0, 0);
			for (int s = 0; s < samples_per_pixel; s++)
			{
				auto u = (i + random_float()) / (image_width-1);
				auto v = (j + random_float()) / (image_height-1);
				ray r = cam.getRay(u, v);
				tmpc += ray_color(r, world, max_depth);
			}
			rgbf c = generateColor(tmpc, samples_per_pixel, 2);
			pic.set(i, j, c);
		}
	}
	generateBmp24("outputs/material.bmp", pic);
}