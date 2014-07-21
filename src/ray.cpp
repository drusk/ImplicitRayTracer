#include "ray.h"

Ray::Ray(Vector3D origin, Vector3D direction)
    : origin(origin), direction(direction)
{
    this->direction.Normalize();
}

Vector3D Ray::GetOrigin() const
{
    return origin;
}

Vector3D Ray::GetDirection() const
{
    return direction;
}

Vector3D Ray::Follow(double distance) const
{
    return origin + direction * distance;
}
