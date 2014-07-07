#ifndef POINT_H_
#define POINT_H_

class Point
{
public:
	Point(double x, double y);

	double GetX();
	double GetY();

private:
	double x;
	double y;
};

#endif
