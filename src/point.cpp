#include "point.h"

Point::Point(double x, double y)
	: x(x), y(y)
{
}

double Point::GetX()
{
	return x;
}

double Point::GetY()
{
	return y;
}
