#include "sphere.h"

#include <cmath>

Sphere::Sphere(Vector3D center, double radius, Vector3D surfaceColour,
		double reflectivity, double transparency)
	: center(center),
	  radius(radius),
	  radiusSquared(radius * radius),
	  surfaceColour(surfaceColour),
	  reflectivity(reflectivity),
	  transparency(transparency),
	  isLightSource(false)
{
}

Vector3D Sphere::GetCenter()
{
	return center;
}

Vector3D Sphere::GetSurfaceColour()
{
	return surfaceColour;
}

void Sphere::SetEmissionColour(Vector3D colour)
{
	emissionColour = colour;
	isLightSource = true;
}

Vector3D Sphere::GetEmissionColour()
{
	return emissionColour;
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

Vector3D Sphere::GetNormal(Vector3D intersectionPoint)
{
	Vector3D normal = intersectionPoint - center;
	normal.Normalize();
	return normal;
}

bool Sphere::IsTransparent()
{
	return transparency > 0;
}

bool Sphere::IsTransparentOrReflective()
{
	return IsTransparent() || reflectivity > 0;
}

Vector3D Sphere::CalculateEffectiveSurfaceColour(Vector3D reflection,
		Vector3D refraction, double fresnelEffect)
{
	Vector3D externalColour = reflection * fresnelEffect +
			refraction * (1 - fresnelEffect) * transparency;

	return externalColour * surfaceColour;
}
