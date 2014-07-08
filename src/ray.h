#ifndef RAY_H_
#define RAY_H_

#include "vector.h"

class Ray
{
public:
	Ray(Vector3D origin, Vector3D direction);

	Vector3D GetOrigin();
	Vector3D GetDirection();

private:
	Vector3D origin;
	Vector3D direction;
};

#endif
