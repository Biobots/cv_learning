#include "img.hpp"
#include "vec.hpp"
#include "ray.hpp"

int main(int argc, const char** argv)
{
	Img pic(256, 256);
	for (size_t i = 0; i < 256; i++)
	{
		for (size_t j = 0; j < 256; j++)
		{
			int idx = (i * 256 + j) * 3;
			pic.set(j, i, rgb(j, j, i));
		}
	}

	vec<int, 2> v(11.3,12.1);
	vec<int, 2> m = -v;
	vec<int, 2> a = v - m;
	std::cout << a.data[1] << std::endl;
	rgb c1(100,100,100);
	rgb c2(11,11,11);
	rgb c3 = c1 + c2;
	std::cout << c3.r() << std::endl;
	vec3<float> f1(1.4,2.0,3.1);
	vec3<float> f2 = f1 + 1.2;
	std::cout << f2.x() << std::endl;
	generateBmp24("outputs/test.bmp", pic);
	return 0;
}