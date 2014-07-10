#include "sphere.h"

#include <cmath>

Sphere::Sphere(Vector3D center, double radius, Vector3D surfaceColour,
		double transparency, double reflectivity)
	: center(center),
	  radius(radius),
	  radiusSquared(radius * radius),
	  surfaceColour(surfaceColour),
	  transparency(transparency),
	  reflectivity(reflectivity),
	  isLightSource(false)
{
}

void Sphere::SetEmissionColour(Vector3D colour)
{
	emissionColour = colour;
	isLightSource = true;
}

bool Sphere::IsLightSource()
{
	return isLightSource;
}

bool Sphere::Intersect(Ray ray, double *nearPoint, double *farPoint)
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

	*nearPoint = projectionAlongRay - distanceFromCenterToIntersection;
	*farPoint = projectionAlongRay + distanceFromCenterToIntersection;

	return true;
}
