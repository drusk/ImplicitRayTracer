#include "vector.h"

#include <cmath>

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

double Vector3D::Length()
{
	return sqrt(pow(GetX(), 2) + pow(GetY(), 2) + pow(GetZ(), 2));
}

void Vector3D::Normalize()
{
	double length = Length();

	if (length > 0) {
		x = x / length;
		y = y / length;
		z = z / length;
	}
}

void Vector3D::Reverse()
{
	x = -x;
	y = -y;
	z = -z;
}

Vector3D Vector3D::operator+(const Vector3D &otherVector) const
{
	return Vector3D(
			GetX() + otherVector.GetX(),
			GetY() + otherVector.GetY(),
			GetZ() + otherVector.GetZ());
}

Vector3D Vector3D::operator-(const Vector3D &otherVector) const
{
	return Vector3D(
			GetX() - otherVector.GetX(),
			GetY() - otherVector.GetY(),
			GetZ() - otherVector.GetZ());
}

Vector3D Vector3D::operator*(double scalingFactor) const
{
	return Vector3D(
			GetX() * scalingFactor,
			GetY() * scalingFactor,
			GetZ() * scalingFactor);
}

Vector3D Vector3D::operator*(const Vector3D &otherVector) const
{
	return Vector3D(
			GetX() * otherVector.GetX(),
			GetY() * otherVector.GetY(),
			GetZ() * otherVector.GetZ());
}

Vector3D operator*(double scalingFactor, const Vector3D &vector)
{
	return vector * scalingFactor;
}
