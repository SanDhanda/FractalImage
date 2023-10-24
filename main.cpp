//Name : FractalCreator.cpp

#include <iostream>
#include "Bitmap.h"
#include "Mandlebrot.h"
#include <cstdint>;
#include <memory>
#include <math.h>
#include "ZoomList.h"
#include "FractalCreator.h"
#include "RGB.h"
using namespace std;



int main() {
	int const Width = 800;
	int const Height = 600;

	RGB rgb1(4, 5, 6);
	RGB rgb2(1, 2, 3);
	RGB rgb3 = rgb1 - rgb2;
	FractalCreator fc(Width, Height);

	fc.AddRange(0.0, RGB(0, 0, 0));
	fc.AddRange(0.3, RGB(255, 0, 0));
	fc.AddRange(0.5, RGB(255, 255, 0));
	fc.AddRange(1.0, RGB(255, 255, 255));

	fc.AddZoom(Zoom(295, Height - 202, 0.1));
	fc.AddZoom(Zoom(312, Height - 304, 0.1));
	fc.run("test3.bmp");

	cout << "Finished" << endl;

	return 0;
}