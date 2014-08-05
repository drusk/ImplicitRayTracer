#include "intersecter.h"

#include <cmath>

GeometricRayIntersecter::GeometricRayIntersecter(Vector3D center, 
        double radius)
    : center(center), radiusSquared(radius * radius)
{
}

bool GeometricRayIntersecter::Intersect(Ray ray, double* distance)
{
    Vector3D rayToCenter = center - ray.GetOrigin();

    double projectionAlongRay = rayToCenter.DotProduct(ray.GetDirection());

    if (projectionAlongRay < 0) {
        /* Behind ray origin, so no intersection. */
        return false;
    }

    /*
     * Using properties of triangle: h^2 = x^2 + y^2
     * centerToRay is hypotenuse.
     */
    double squaredDistanceFromCenterToIntersection = rayToCenter.DotProduct(
            rayToCenter) - projectionAlongRay * projectionAlongRay;

    if (squaredDistanceFromCenterToIntersection > radiusSquared) {
        /* Ray shoots wide, doesn't hit sphere. */
        return false;
    }

    double distanceFromCenterToIntersection = sqrt(radiusSquared -
            squaredDistanceFromCenterToIntersection);

    *distance = projectionAlongRay - distanceFromCenterToIntersection;

    return true;
}
