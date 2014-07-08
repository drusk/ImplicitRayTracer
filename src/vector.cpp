#include "vector.h"

Vector3D::Vector3D()
	: x(0), y(0), z(0)
{
}

Vector3D::Vector3D(double x, double y, double z)
	: x(x), y(y), z(z)
{
}

double Vector3D::GetX() const
{
	return x;
}

double Vector3D::GetY() const
{
	return y;
}

double Vector3D::GetZ() const
{
	return z;
}

double Vector3D::DotProduct(const Vector3D &otherVector) const
{
	return GetX() * otherVector.GetX() + GetY() * otherVector.GetY() +
			GetZ() * otherVector.GetZ();
}
