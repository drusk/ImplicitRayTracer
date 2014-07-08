#ifndef SPHERE_H_
#define SPHERE_H_

#include "vector.h"

class Sphere
{
public:
	Sphere(Vector3D center, double radius, Vector3D surfaceColour,
			double transparency, double reflectivity);

	/**
	 * Sets the emission colour, making this object a light source.
	 */
	void SetEmissionColour(Vector3D colour);

	/**
	 * Returns true if this object is a light source.  It can be made
	 * a light source by setting the emission colour (SetEmissionColour).
	 */
	bool IsLightSource();

private:
	Vector3D center;
	double radius;
	Vector3D surfaceColour;
	double transparency;
	double reflectivity;

	bool isLightSource;
	Vector3D emissionColour;
};

#endif
