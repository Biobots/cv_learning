#include <vec.hpp>
#include <ray.hpp>

rgbf ray_color(const ray& r) {
	vec3f unit_direction = unit_vector(r.direction());
	float t = 0.5*(unit_direction.y() + 1.0);
	return (1.0-t)*rgbf(1.0, 1.0, 1.0) + t*rgbf(0.5, 0.7, 1.0);
}

int main()
{

}