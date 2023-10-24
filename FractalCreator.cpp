#include "FractalCreator.h"
#include "Mandlebrot.h"
#include <memory>
#include <iostream>
#include <cstdint>;
#include <cassert>
using namespace std;

void FractalCreator::run(string name) {


	CalculateIterations();
	CalculateRangeTotals();
	DrawFractal();
	WriteBitmap(name);
}

FractalCreator::FractalCreator(int width, int height) :m_width(width), m_height(height),
m_histogram(new int[Mandlebrot::MAX_ITERATIONS] {0}), m_fractal(new int[m_width * m_height] {0}),
m_zoomList(width, height), m_bitmap(width, height) {
	AddZoom(Zoom(m_width / 2, m_height / 2, 4.0 / m_width));
}

void FractalCreator::CalculateIterations() {

	for (int y = 0; y < m_height; y++) {
		for (int x = 0; x < m_width; x++) {

			pair<double, double> coords = m_zoomList.doZoom(x, y);
			int iterations = Mandlebrot::getIterations(coords.first, coords.second);
			m_fractal[y * m_width + x] = iterations;
			if (iterations != Mandlebrot::MAX_ITERATIONS) {
				m_histogram[iterations]++;
			}
		}
	}
}
void FractalCreator::DrawFractal() {

	RGB startColour(0, 0, 0);
	RGB endColour(0, 0, 200);
	RGB colourDiff = endColour - startColour;
	int total = 0;
	for (int i = 0; i < Mandlebrot::MAX_ITERATIONS; i++) {
		total += m_histogram[i];
	}
	for (int y = 0; y < m_height; y++) {
		for (int x = 0; x < m_width; x++) {

			int iterations = m_fractal[y * m_width + x];
			int range = GetRange(iterations);
			int rangeTotal = m_rangeTotals[range];
			int rangeStart = m_ranges[range];

			RGB& startColour = m_colours[range];
			RGB& endColour = m_colours[range + 1];
			RGB colourDiff = endColour - startColour;

			uint8_t red = 0;
			uint8_t blue = 0;
			uint8_t green = 0;


			if (iterations != Mandlebrot::MAX_ITERATIONS) {

				int totalPixels = 0;
				for (int i = rangeStart; i <= iterations; i++) {
					totalPixels += m_histogram[i];
				}
				red = startColour.r + colourDiff.r * (double)totalPixels / rangeTotal;
				green = startColour.g + colourDiff.g * (double)totalPixels / rangeTotal;
				blue = startColour.b + colourDiff.b * (double)totalPixels / rangeTotal;
			}
			m_bitmap.setPixel(x, y, red, green, blue);

		}
	}
}
void FractalCreator::WriteBitmap(string name) {
	m_bitmap.write(name);
}
void FractalCreator::AddZoom(const Zoom& zoom) {
	m_zoomList.add(zoom);
}

FractalCreator::~FractalCreator() {

}

void FractalCreator::AddRange(double range, const RGB& rgb) {
	m_ranges.push_back(range * Mandlebrot::MAX_ITERATIONS);
	m_colours.push_back(rgb);
	if (m_bGotFirstRange) {
		m_rangeTotals.push_back(0);
	}
	m_bGotFirstRange = true;
}

void FractalCreator::CalculateRangeTotals() {

	int rangeIndex = 0;
	for (int i = 0; i < Mandlebrot::MAX_ITERATIONS; i++) {
		int pixels = m_histogram[i];
		if (i >= m_ranges[rangeIndex + 1]) {
			rangeIndex++;
		}
		m_rangeTotals[rangeIndex] += pixels;
	}
}

int FractalCreator::GetRange(int iterations) const {
	int range = 0;

	for (int i = 1; i < m_ranges.size(); i++) {
		range = i;
		if (m_ranges[i] > iterations) {
			break;
		}
		

	}
	range--;
	assert(range > -1);
	assert(range < m_ranges.size());
	return range;
}