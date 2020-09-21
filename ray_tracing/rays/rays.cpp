#include <vec.hpp>
#include <img.hpp>
#include <ray.hpp>

rgbf ray_color(const ray& r) {
	vec3f unit_direction = r.direction().unit_vector();
	float t = 0.5*(unit_direction.y() + 1.0);
	return (1.0-t)*rgbf(1.0, 1.0, 1.0) + t*rgbf(0.5, 0.7, 1.0);
}

int main()
{
	const auto aspect_ratio = 16.0 / 9.0;
	const int image_width = 400;
	const int image_height = static_cast<int>(image_width / aspect_ratio);

	auto viewport_height = 2.0;
	auto viewport_width = aspect_ratio * viewport_height;
	auto focal_length = 1.0;

	auto origin = vec3f(0, 0, 0);
	auto horizontal = vec3f(viewport_width, 0, 0);
	auto vertical = vec3f(0, viewport_height, 0);
	auto lower_left_corner = origin - horizontal/2 - vertical/2 - vec3f(0, 0, focal_length);

	Img pic(image_width, image_height);
	for(int i = 0; i < image_width; i++)
	{
		for(int j = 0; j < image_height; j++)
		{
			auto u = double(i) / (image_width-1);
			auto v = double(j) / (image_height-1);

			ray r(origin, lower_left_corner + u*horizontal + v*vertical - origin);
			rgbf c = ray_color(r);
			pic.set(i, j, c);
		}
	}
	generateBmp24("b.bmp", pic);
}