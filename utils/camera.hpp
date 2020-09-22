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
	vec3f w, u, v;
	float lens_radius;
public:
	Camera(vec3f lookfrom, vec3f lookat, vec3f up, float vfov, float aspect_ratio, float aperture, float focus_dist)
	{
		float theta = degrees_to_radians(vfov);
        float h = tan(theta/2);
        float viewport_height = 2.0 * h;
        float viewport_width = aspect_ratio * viewport_height;

		w = (lookfrom - lookat).normalize();
		u = cross(up, w).normalize();
		v = cross(w, u);

		_origin = lookfrom;
		_horizontal = focus_dist * viewport_width * u;
		_vertical = focus_dist * viewport_height * v;
		_start_corner = _origin - focus_dist * w - _horizontal / 2 - _vertical / 2;

		lens_radius = aperture / 2;
	}

	ray getRay(float s, float t)
	{
		vec3f rd = lens_radius * random_in_unit_disk();
		vec3f offset = u * rd.x() + v * rd.y();
		return ray(_origin + offset, _start_corner + s * _horizontal + t * _vertical - _origin - offset);
	}
};

#endif