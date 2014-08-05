#include "implicits/surface.h"

ImplicitSphere::ImplicitSphere(Vector3D center, double radius)
    : center(center), radius(radius)
{
}

Box ImplicitSphere::BoundingBox()
{
    // The scale factor is arbitrary, it just needs to be > 2 so that the 
    // box is slightly larger than the sphere.
    return Box(center, 2.1 * radius);
}

double ImplicitSphere::ImplicitFunction(Vector3D point)
{
    return (point - center).LengthSquared() - radius * radius;
}

Vector3D ImplicitSphere::Gradient(Vector3D point)
{
    Vector3D diff = (point - center);
    return Vector3D(2 * diff.GetX(), 2 * diff.GetY(), 2 * diff.GetZ());
}

double ImplicitSphere::DirectionalGradient(Ray ray, double t)
{
    return Gradient(ray.Follow(t)).DotProduct(ray.GetDirection());
}

double ImplicitSphere::LipschitzConstant(Vector3D minPoint, Vector3D maxPoint)
{
    return (2.0 / radius) * maxPoint.Length();
}

double ImplicitSphere::GradLipschitzConstant(Ray ray, double t1, double t2)
{
    return (2.0 / radius) * ray.GetDirection().LengthSquared();
}
