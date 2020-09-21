#ifndef CV_IMG_HPP
#define CV_IMG_HPP

#include <iostream>
#include <string>
#include <fstream>
#include "defines.hpp"
#include "vec.hpp"

using namespace std;

enum IMG_TYPE
{
	BMP8BIT,
	BMP24BIT
};

typedef unsigned short WORD;
typedef unsigned int DWORD;
typedef int LONG;

#pragma pack(2)

struct BITMAPFILEHEADER
{
	WORD bfType;
	DWORD bfSize;
	WORD bfReserved1;
	WORD bfReserved2;
	DWORD bfOffBits;
};

typedef struct BITMAPINFOHEADER{
	DWORD biSize;
	LONG biWidth;
	LONG biHeight;
	WORD biPlanes;
	WORD biBitCount;
	DWORD biCompression;
	DWORD biSizeImage;
	LONG biXPelsPerMeter;
	LONG biYPelsPerMeter;
	DWORD biClrUsed;
	DWORD biClrImportant;
};

class Img
{
private:
	rgb* _data;
	uchar* _raw;
	uint _width;
	uint _height;
public:
	Img(uint width, uint height)
	{
		_width = width;
		_height = height;
		_data = new rgb[width * height];
		_raw = new uchar[width * height * 3];
	}
	~Img()
	{
		delete _data;
		delete _raw;
	}
	rgb get(uint x, uint y)
	{
		uint idx = x + y * _width;
		return _data[idx];
	}
	void set(uint x, uint y, rgb val)
	{
		uint idx = x + y * _width;
		_data[idx] = val;
	}
	uchar* raw()
	{
		uint num = _width * _height;
		for (int i = 0; i < num; i++)
		{
			copy(_data[i].data, _data[i].data+3, _raw+3*i);
		}
		return _raw;
	}
	uint width()
	{
		return _width;
	}
	uint height()
	{
		return _height;
	}
};

int generateBmp24(string name, Img img)
{
	int imagDataSize = img.height()*img.width() * 3; // imag data size

	//位图第一部分，位图文件头
	BITMAPFILEHEADER *bfHeader{ new BITMAPFILEHEADER };
	bfHeader->bfType = 0x4d42;  // string"BM"  
	bfHeader->bfSize = imagDataSize + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER); // file size
	bfHeader->bfReserved1 = 0; // reserved  
	bfHeader->bfReserved2 = 0; // reserved  
	bfHeader->bfOffBits = sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER); // real data 位置

	//位图第二部分，位图信息头  
	BITMAPINFOHEADER *biHeader{ new BITMAPINFOHEADER };
	biHeader->biSize = sizeof(BITMAPINFOHEADER);
	biHeader->biWidth = img.width();
	biHeader->biHeight = img.height();//BMP图片从最后一个点开始扫描，显示时图片是倒着的，所以用-height，这样图片就正了  
	biHeader->biPlanes = 1;//为1，不用改  
	biHeader->biBitCount = 24; // 每个像素占用的bit
	biHeader->biCompression = 0;//不压缩  
	biHeader->biSizeImage = imagDataSize;
	biHeader->biXPelsPerMeter = 0;//像素每米  
	biHeader->biYPelsPerMeter = 0;
	biHeader->biClrUsed = 0;//已用过的颜色，24位的为0  
	biHeader->biClrImportant = 0;//每个像素都重要 

	std::fstream file(name, std::ios::out | std::ios::binary);
	file.write((char*)bfHeader, sizeof(BITMAPFILEHEADER));
	file.write((char*)biHeader, sizeof(BITMAPINFOHEADER));
	file.write((char*)img.raw(), imagDataSize);
	file.close();

	return 0;
}

int generateBmp24(string name, int width, int height, unsigned char* data)
{
	int imagDataSize = height*width * 3; // imag data size

	//位图第一部分，位图文件头
	BITMAPFILEHEADER *bfHeader{ new BITMAPFILEHEADER };
	bfHeader->bfType = 0x4d42;  // string"BM"  
	bfHeader->bfSize = imagDataSize + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER); // file size
	bfHeader->bfReserved1 = 0; // reserved  
	bfHeader->bfReserved2 = 0; // reserved  
	bfHeader->bfOffBits = sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER); // real data 位置

	//位图第二部分，位图信息头  
	BITMAPINFOHEADER *biHeader{ new BITMAPINFOHEADER };
	biHeader->biSize = sizeof(BITMAPINFOHEADER);
	biHeader->biWidth = width;
	biHeader->biHeight = height;//BMP图片从最后一个点开始扫描，显示时图片是倒着的，所以用-height，这样图片就正了  
	biHeader->biPlanes = 1;//为1，不用改  
	biHeader->biBitCount = 24; // 每个像素占用的bit
	biHeader->biCompression = 0;//不压缩  
	biHeader->biSizeImage = imagDataSize;
	biHeader->biXPelsPerMeter = 0;//像素每米  
	biHeader->biYPelsPerMeter = 0;
	biHeader->biClrUsed = 0;//已用过的颜色，24位的为0  
	biHeader->biClrImportant = 0;//每个像素都重要 

	std::fstream file(name, std::ios::out | std::ios::binary);
	file.write((char*)bfHeader, sizeof(BITMAPFILEHEADER));
	file.write((char*)biHeader, sizeof(BITMAPINFOHEADER));
	file.write((char*)data, imagDataSize);
	file.close();

	return 0;
}

#endif // !CV_IMG