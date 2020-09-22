#include <defines.hpp>
#include <vec.hpp>
#include <img.hpp>
#include <ray.hpp>
#include <objects.hpp>
#include <camera_old.hpp>

rgbf ray_color(const ray& r, const Hittable_list& world) {
	hit_record rec;
	vec3f unit_direction = r.direction().normalize();
	if(world.hit(r, 0, infinity, rec))
	{
		return 0.5*(rec.normal + rgbf(1,1,1));
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

	Hittable_list world;
	world.add(make_shared<Sphere>(vec3f(0, 0, -1), 0.5));
	world.add(make_shared<Sphere>(vec3f(0, -100.5, -1), 100));

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
				tmpc += ray_color(r, world);
			}
			tmpc /= samples_per_pixel;
			rgbf c(clamp(tmpc.r(), 0.0, 0.99), clamp(tmpc.g(), 0.0, 0.99), clamp(tmpc.b(), 0.0, 0.99));
			pic.set(i, j, c);
		}
	}
	generateBmp24("outputs/sphere.bmp", pic);
}