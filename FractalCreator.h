#pragma once
#ifndef FRACTALCREATOR_H_
#define FRACTALCREATOR_H_

#include<string>
#include "Zoom.h"
#include "ZoomList.h"
#include "Bitmap.h"
#include "RGB.h"
#include <vector>
using namespace std;

class FractalCreator
{
private:
	int const m_width;
	int const m_height;
	ZoomList m_zoomList;
	Bitmap m_bitmap;
	unique_ptr<int[]> m_histogram;
	unique_ptr<int[]> m_fractal;

	vector<int> m_ranges;
	vector<RGB> m_colours;
	vector<int> m_rangeTotals;

	bool m_bGotFirstRange{ false };

	void CalculateIterations();
	void DrawFractal();
	void WriteBitmap(string name);
	void CalculateRangeTotals();

	int GetRange(int iterations) const;
	

public:
	FractalCreator(int width, int height);
	virtual ~FractalCreator();
	void run(string name);
	void AddZoom(const Zoom& zoom);
	void AddRange(double rangeEnd, const RGB& rgb);
};
#endif
