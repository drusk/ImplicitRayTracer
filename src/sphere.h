#ifndef SPHERE_H_
#define SPHERE_H_

#include "ray.h"
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

	/**
	 * Computes the intersection of the ray with this sphere.  Returns
	 * true if there is an intersection, false otherwise.  If there is
	 * an intersection, the nearPoint and farPoint parameters are used
	 * to return the distance along the ray at which the intersections
	 * occur.
	 */
	bool Intersect(Ray ray, double *nearPoint, double *farPoint);

	/**
	 * Returns the normal of this object at the intersection point provided.
	 * The normal is normalized to a unit vector.
	 */
	Vector3D GetNormal(Vector3D intersectionPoint);

private:
	Vector3D center;
	double radius;
	double radiusSquared;
	Vector3D surfaceColour;
	double transparency;
	double reflectivity;

	bool isLightSource;
	Vector3D emissionColour;
};

#endif
