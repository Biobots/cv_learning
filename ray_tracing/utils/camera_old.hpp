#ifndef CV_CAMERA_HPP
#define CV_CAMERA_HPP

#include <defines.hpp>
#include <vec.hpp>
#include <ray.hpp>

class Camera
{
private:
	vec3f _origin;
	vec3f _start_corner;
	vec3f _horizontal;
	vec3f _vertical;
public:
	Camera()
	{
		float aspect_ratio = 16.0 / 9.0;
		float viewport_height = 2.0;
		float viewport_width = aspect_ratio * viewport_height;
		float focal_length = 1.0;

		_origin = vec3f(0, 0, 0);
		_horizontal = vec3f(viewport_width, 0, 0);
		_vertical = vec3f(0, viewport_height, 0);
		_start_corner = _origin - vec3f(0, 0, focal_length) - _horizontal / 2 - _vertical / 2;
	}

	ray getRay(float u, float v)
	{
		return ray(_origin, _start_corner + u * _horizontal + v * _vertical - _origin);
	}
};

#endif