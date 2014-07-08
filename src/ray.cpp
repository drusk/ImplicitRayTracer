#include "ray.h"

Ray::Ray(Vector3D origin, Vector3D direction)
	: origin(origin), direction(direction)
{
}

Vector3D Ray::GetOrigin()
{
	return origin;
}

Vector3D Ray::GetDirection()
{
	return direction;
}
