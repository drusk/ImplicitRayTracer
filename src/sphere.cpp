#include "sphere.h"

Sphere::Sphere(Vector3D center, double radius, Vector3D surfaceColour,
		double transparency, double reflectivity)
	: center(center),
	  radius(radius),
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
