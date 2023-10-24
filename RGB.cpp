#include "RGB.h"

RGB::RGB(double r, double g, double b):r(r), b(b), g(g)
{
}
RGB operator-(const RGB& first, const RGB& second) {
	return RGB(first.r - second.r, first.g - second.g, first.b - second.b);
	
}


RGB::~RGB()
{
}
