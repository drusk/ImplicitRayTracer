#include "point.h"

#include <iostream>

int main(int argc, char **argv)
{
	Point point(-5.0, 6.0);

	std::cout << "Created point at: " << point.GetX() << ", "
			<< point.GetY() << std::endl;

	return 0;
}
