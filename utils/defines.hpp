#ifndef CV_DEFINES_HPP
#define CV_DEFINES_HPP

#include <limits>
#include <cstdlib>

typedef unsigned char uchar;
typedef unsigned int uint;

const float infinity = std::numeric_limits<float>::infinity();
const float pi = 3.14159265358;

inline float degrees_to_radians(float degrees) {
	return degrees * pi / 180.0;
}

inline float random_float()
{
	return rand() / (RAND_MAX + 1.0);
}

inline float random_float(float min, float max)
{
	return min + (max - min) * random_float();
}

inline float clamp(float x, float min, float max) {
	if (x < min) return min;
	if (x > max) return max;
	return x;
}

#endif