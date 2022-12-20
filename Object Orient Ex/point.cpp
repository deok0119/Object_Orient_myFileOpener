#include "point.h"
#include <math.h>

Point::Point(double x, double y)
	:x(x), y(y){}

double Point::distance(const Point& p) const {
	double dx = x - p.x;
	double dy = y - p.y;
	return sqrt(dx * dx + dy * dy);
}