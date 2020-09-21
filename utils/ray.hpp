#ifndef CV_RAY_HPP
#define CV_RAY_HPP

#include "vec.hpp"

class ray
{
private:
	vec3f _origin;
	vec3f _direction;

public:
	ray() {}
	ray(const vec3f& origin, const vec3f& direction)
	{
		_origin = origin;
		_direction = direction;
	}

	vec3f origin() const { return _origin;}
	vec3f direction() const { return _direction;}

	vec3f at(float t) const
	{
		return _origin + t * _direction;
	} 
};

#endif