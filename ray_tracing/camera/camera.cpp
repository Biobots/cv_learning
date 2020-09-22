#include <defines.hpp>
#include <vec.hpp>
#include <img.hpp>
#include <ray.hpp>
#include <objects.hpp>
#include <camera.hpp>
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

Hittable_list random_scene() {
    Hittable_list world;

    auto ground_material = make_shared<Lambertian>(rgbf(0.5, 0.5, 0.5));
    world.add(make_shared<Sphere>(vec3f(0,-1000,0), 1000, ground_material));

    for (int a = -2; a < 2; a++) {
        for (int b = -2; b < 2; b++) {
            auto choose_mat = random_float();
            vec3f center(a + 0.9*random_float(), 0.2, b + 0.9*random_float());

            if ((center - vec3f(4, 0.2, 0)).length() > 0.9) {
                shared_ptr<Material> Sphere_material;

                if (choose_mat < 0.8) {
                    // diffuse
                    auto albedo = rgbf::random() * rgbf::random();
                    Sphere_material = make_shared<Lambertian>(albedo);
                    world.add(make_shared<Sphere>(center, 0.2, Sphere_material));
                } else if (choose_mat < 0.95) {
                    // metal
                    auto albedo = rgbf::random(0.5, 1);
                    auto fuzz = random_float(0, 0.5);
                    Sphere_material = make_shared<Metal>(albedo, fuzz);
                    world.add(make_shared<Sphere>(center, 0.2, Sphere_material));
                } else {
                    // glass
                    Sphere_material = make_shared<Dielectric>(1.5);
                    world.add(make_shared<Sphere>(center, 0.2, Sphere_material));
                }
            }
        }
    }

    auto material1 = make_shared<Dielectric>(1.5);
    world.add(make_shared<Sphere>(vec3f(0, 1, 0), 1.0, material1));

    auto material2 = make_shared<Lambertian>(rgbf(0.4, 0.2, 0.1));
    world.add(make_shared<Sphere>(vec3f(-4, 1, 0), 1.0, material2));

    auto material3 = make_shared<Metal>(rgbf(0.7, 0.6, 0.5), 0.0);
    world.add(make_shared<Sphere>(vec3f(4, 1, 0), 1.0, material3));

    return world;
}

int main()
{
	const auto aspect_ratio = 3.0 / 2.0;
	const int image_width = 1200;
	const int image_height = static_cast<int>(image_width / aspect_ratio);
	const int samples_per_pixel = 500;
	const int max_depth = 50;

	Hittable_list world = random_scene();

	Camera cam(vec3f(13,2,3), vec3f(0,0,0), vec3f(0,1,0), 20.0, aspect_ratio, 0.1, 10.0);

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
	generateBmp24("outputs/camera.bmp", pic);
}