#include "implicits/surface.h"

#include <cmath>

SphereSurface::SphereSurface(Vector3D center, double radius)
    : center(center), radius(radius)
{
}

Box SphereSurface::BoundingBox()
{
    // The scale factor is arbitrary, it just needs to be > 2 so that the 
    // box is slightly larger than the sphere.
    return Box(center, 2.1 * radius);
}

double SphereSurface::ImplicitFunction(Vector3D point)
{
    return (point - center).LengthSquared() - radius * radius;
}

Vector3D SphereSurface::Gradient(Vector3D point)
{
    Vector3D diff = (point - center);
    return Vector3D(2 * diff.GetX(), 2 * diff.GetY(), 2 * diff.GetZ());
}

double SphereSurface::DirectionalGradient(Ray ray, double t)
{
    return Gradient(ray.Follow(t)).DotProduct(ray.GetDirection());
}

double SphereSurface::LipschitzConstant(Vector3D minPoint, Vector3D maxPoint)
{
    return (2.0 / radius) * 
            GetAbsoluteMaxDiffFromCenter(minPoint, maxPoint).Length();
}

double SphereSurface::GradLipschitzConstant(Ray ray, double t1, double t2)
{
    return (2.0 / radius) * ray.GetDirection().LengthSquared();
}

double SphereSurface::ChooseAbsoluteMax(double value1, double value2)
{
    double absValue1 = std::abs(value1);
    double absValue2 = std::abs(value2);
    
    return absValue1 > absValue2 ? absValue1 : absValue2;
}

Vector3D SphereSurface::GetAbsoluteMaxDiffFromCenter(Vector3D minPoint, 
        Vector3D maxPoint)
{
    double x = ChooseAbsoluteMax(minPoint.GetX() - center.GetX(),
            maxPoint.GetX() - center.GetX());
    double y = ChooseAbsoluteMax(minPoint.GetY() - center.GetY(),
            maxPoint.GetY() - center.GetY());
    double z = ChooseAbsoluteMax(minPoint.GetZ() - center.GetZ(),
            maxPoint.GetZ() - center.GetZ());
    
    return Vector3D(x, y, z);
}
