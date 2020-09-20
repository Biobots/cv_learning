#include "img.hpp"

int main(int argc, const char** argv)
{
	uchar pic[256*256*3];
	for (size_t i = 0; i < 256; i++)
	{
		for (size_t j = 0; j < 256; j++)
		{
			int idx = (i * 256 + j) * 3;
			pic[idx] = i;
			pic[idx + 1] = j;
			pic[idx + 2] = i;
		}
	}

	generateBmp24("a.bmp", 256, 256, pic);
	return 0;
}