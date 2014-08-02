#include "implicits/surface.h"

ImplicitSphere::ImplicitSphere(Vector3D center, double radius)
    : center(center), radius(radius)
{
}

double ImplicitSphere::ImplicitFunction(Vector3D point)
{
    return (point - center).LengthSquared() - radius * radius;
}

double ImplicitSphere::LipschitzConstant(Vector3D minPoint, Vector3D maxPoint)
{
    return (2.0 / radius) * maxPoint.Length();
}

double ImplicitSphere::GradLipschitzConstant(Ray ray, double t1, double t2)
{
    return (2.0 / radius) * ray.GetDirection().LengthSquared();
}
