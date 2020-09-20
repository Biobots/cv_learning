#ifndef CV_IMG_HPP
#define CV_IMG_HPP

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

enum IMG_TYPE
{
	BMP8BIT,
	BMP24BIT
};

typedef unsigned short WORD;
typedef unsigned int DWORD;
typedef int LONG;

typedef unsigned char uchar;
typedef unsigned int uint;

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

struct vec3
{
	uchar x;
	uchar y;
	uchar z;
};


class Img
{
private:
	uchar* _data;
	uint _width;
	uint _height;
	uint _channel;
public:
	Img(uint width, uint height, uint channel)
	{
		_width = width;
		_height = height;
		_channel = channel;
		_data = new uchar[width * height * channel];
	}
	~Img()
	{
		delete _data;
	}
	vec3 get(uint x, uint y)
	{
		vec3 rst;
		uint idx = x + y * _width;
		rst.x = _data[idx];
		rst.y = _data[idx + 1];
		rst.z = _data[idx + 2];
		return rst;
	}
};

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
}

#endif // !CV_IMG