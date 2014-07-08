#include "vector.h"

#include <iostream>

int main(int argc, char **argv)
{
	Vector3D vector;

	std::cout << "Created vector: " << vector.GetX() << ", "
			<< vector.GetY() << ", " << vector.GetZ() << std::endl;

	return 0;
}
