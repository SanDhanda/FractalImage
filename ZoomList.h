#pragma once
#ifndef ZOOMLIST_H_
#define ZOOMLIST_H_

#include "Zoom.h"
#include <vector>
#include <utility>

class ZoomList
{
private:
	double m_xCenter{ 0.0 };
	double m_yCenter{ 0.0 };
	double m_Scale{ 1.0 };

	int m_width{ 0 };
	int m_height{ 0 };
	std::vector<Zoom> zooms;
public:
	ZoomList(int widht, int height);
	void add(const Zoom& zoom);
	std::pair<double, double> doZoom(int x, int y);
};

#endif

