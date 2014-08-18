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

double SphereSurface::DirectionalGradient(Ray ray, double t)
{
    double dirX = ray.GetDirection().GetX();
    double dirY = ray.GetDirection().GetY();
    double dirZ = ray.GetDirection().GetZ();
    
    double originX = ray.GetOrigin().GetX();
    double originY = ray.GetOrigin().GetY();
    double originZ = ray.GetOrigin().GetZ();
    
    return 2 * (pow(dirX, 2) * t + dirX * originX - dirX * center.GetX()
            + pow(dirY, 2) * t + dirY * originY - dirY * center.GetY()
            + pow(dirZ, 2) * t + dirZ * originZ - dirZ * center.GetZ());
}

double SphereSurface::LipschitzConstant(Vector3D minPoint, Vector3D maxPoint)
{
    double x = ChooseAbsoluteMax(minPoint.GetX() - 1, maxPoint.GetX() - 1);
    double y = ChooseAbsoluteMax(minPoint.GetY() - 1, maxPoint.GetY() - 1);
    double z = ChooseAbsoluteMax(minPoint.GetZ() - 1, maxPoint.GetZ() - 1);
    
    return 2.0 * Vector3D(x, y, z).Length();
}

double SphereSurface::GradLipschitzConstant(Ray ray, double t1, double t2)
{
    return 2.0 * ray.GetDirection().LengthSquared();
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
