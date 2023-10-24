#include "Bitmap.h"
#include "BitmapInfoHeader.h"
#include "BitmapFileHeader.h"
#include <iostream>
#include <fstream>

using namespace std;

Bitmap::Bitmap() {

}
Bitmap::Bitmap(int width, int height) :
	m_width(width), m_height(height), m_pPixels(
		new uint8_t[width * height * 3]{ }) {

}


bool Bitmap::write(string filename) {

	BitmapFileHeader fileHeader;
	BitmapInfoHeader infoHeader;


	fileHeader.fileSize = sizeof(BitmapFileHeader) + sizeof(BitmapInfoHeader)
		+ m_width * m_height * 3;
	fileHeader.dataOffset = sizeof(BitmapFileHeader) + sizeof(BitmapInfoHeader);

	infoHeader.width = m_width;
	infoHeader.height = m_height;

	ofstream file;
	file.open(filename, ios::out | ios::binary);

	if (!file) {
		return false;
	}

	file.write((char*)&fileHeader, sizeof(fileHeader));
	file.write((char*)&infoHeader, sizeof(infoHeader));
	file.write((char*)m_pPixels.get(), m_width * m_height * 3);

	file.close();

	if (!file) {
		return false;
	}

	return true;
}

void Bitmap::setPixel(int x, int y, uint8_t red, uint8_t green, uint8_t blue) {
	uint8_t* pPixel = m_pPixels.get();
	pPixel += (3* y) * m_width + (3* x); //number of bytes in all rows we want + number of columns. x3 because of 3 bytes
	pPixel[0] = blue;
	pPixel[1] = red;
	pPixel[2] = green;

}

Bitmap::~Bitmap() {

}

void Bitmap::setHeight(int height) {
	m_height = height;
}
void Bitmap::setWidth(int width) {
	m_width = width;
}
void Bitmap::setPixelsptr(int size){



	
}