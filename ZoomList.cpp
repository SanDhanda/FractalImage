#include "ZoomList.h"
using namespace std;

ZoomList::ZoomList() {

}

ZoomList::ZoomList(int width, int height): m_width(width), m_height(height) {

}

void ZoomList::add(const Zoom& zoom) {
	zooms.push_back(zoom);
	m_xCenter += (zoom.x - m_width / 2)*m_Scale;
	m_yCenter += -(zoom.y - m_height / 2)*m_Scale;

	m_Scale *= zoom.scale;

}

std::pair<double, double> ZoomList::doZoom(int x, int y) {

	double xFractal = (x - m_width / 2) * m_Scale + m_xCenter;
	double yFractal = (y - m_height / 2) * m_Scale + m_yCenter;

	return std::pair<double, double>(xFractal, yFractal);
}