#ifndef BITMAPFILEHEADER_H_
#define BITMAPFILEHEADER_H_
#include <cstdint> //for 32 bit int
using namespace std;
#pragma pack(2) //allign all properties to 2 bytre boundaries rather than padding
struct BitmapFileHeader {
	char header[2]{ 'B', 'M' };
	int32_t fileSize;
	int32_t reserved{ 0 };
	int32_t dataOffset;
};

#endif