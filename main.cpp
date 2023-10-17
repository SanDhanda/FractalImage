//Name : FractalCreator.cpp

#include <iostream>
#include "Bitmap.h"
#include "Mandlebrot.h"
#include <cstdint>;
#include <memory>
#include <math.h>
#include "ZoomList.h"
using namespace std;



int main() {
	int const Width = 800;
	int const Height = 600;
	Bitmap bitmap(Width, Height);

	double min = 99999999;
	double max = -99999999;

	ZoomList zoomList(Width, Height);
	zoomList.add(Zoom(Width / 2, Height / 2, 2.0/Width));

	unique_ptr<int[]> histogram(new int[Mandlebrot::MAX_ITERATIONS] {0});
	unique_ptr<int[]> fractal(new int[Width * Height] {0});

	for (int y = 0; y < Height; y++) {
		for (int x = 0; x < Width; x++) {

			pair<double, double> coords = zoomList.doZoom(x, y);
			int iterations = Mandlebrot::getIterations(coords.first, coords.second);
			fractal[y * Width + x] = iterations;
			if (iterations != Mandlebrot::MAX_ITERATIONS) {
				histogram[iterations]++;
			}
		}
	}

	int total = 0;
	for (int i = 0; i < Mandlebrot::MAX_ITERATIONS; i++) {
		total += histogram[i];
	}
	for (int y = 0; y < Height; y++) {
		for (int x = 0; x < Width; x++) {
			uint8_t red = 0;
			uint8_t blue = 0;
			uint8_t green = 0;
			int iterations = fractal[y * Width + x];

			if (iterations != Mandlebrot::MAX_ITERATIONS) {

				double hue = 0.0;
				for (int i = 0; i <= iterations; i++) {
					hue += ((double)histogram[i]) / total;
				}
				green = pow(255, hue);
			}

			bitmap.setPixel(x, y, red, green, blue);

		}
	}
	bitmap.write("test.bmp");

	cout << "Finished" << endl;

	return 0;
}