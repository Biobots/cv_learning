#ifndef CV_COLOR_HPP
#define CV_COLOR_HPP

#include <defines.hpp>
#include <vec.hpp>

rgbf generateColor(const rgbf& input, int samples_per_pixel, float gamma)
{
	rgbf output = input / samples_per_pixel;

	output.r() = pow(output.r(), 1/gamma);
	output.g() = pow(output.g(), 1/gamma);
	output.b() = pow(output.b(), 1/gamma);

	output.r() = clamp(output.r(), 0.0, 0.99);
	output.g() = clamp(output.g(), 0.0, 0.99);
	output.b() = clamp(output.b(), 0.0, 0.99);

	return output;
}

#endif