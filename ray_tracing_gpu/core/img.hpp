#ifndef CV_RTGPU_IMG_HPP
#define CV_RTGPU_IMG_HPP

#include <utils.hpp>
#include <vec.hpp>

enum ImgType
{
	RGB8UI,
	BGR8UI,
	RGB32F
};

class Img
{
private:
	u32 _width;
	u32 _height;
	u32 _size;
	rgb* _data;
	bool* _dirty;
	u8* _raw;

public:
	Img(u32 width, u32 height)
	{
		_raw = new u8[width * height * 3];
		_data = new rgb[width * height];
		_dirty = new bool[width * height]{false};
		_size = width * height;
	}
	~Img()
	{
		delete[] _raw;
		delete[] _data;
		delete[] _dirty;
	}
	rgb& at(u32 x, u32 y)
	{
		u32 idx = _width * y + x;
		_dirty[idx] = true;
		return _data[idx];
	}
	const rgb& read(u32 x, u32 y)
	{
		u32 idx = _width * y + x;
		return _data[idx];
	}
	void write(u32 x, u32 y, rgb val)
	{
		u32 idx = _width * y + x;
		_data[idx].r() = val.r();
		_data[idx].g() = val.g();
		_data[idx].b() = val.b();
		_dirty[idx] = true;
		return;
	}
	u8* getRaw()
	{
		for(int i = 0; i < _size; i++)
		{
			if(_dirty[i])
			{
				std::copy(_data[i].data, _data[i].data + 3, _raw + i * 3);
			}
		}
		return _raw;
	}
};

#endif