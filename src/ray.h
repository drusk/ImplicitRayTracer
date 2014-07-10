#ifndef RAY_H_
#define RAY_H_

#include "vector.h"

class Ray
{
public:
	/**
	 * Creates a ray given its origin point and direction in 3D space.
	 */
	Ray(Vector3D origin, Vector3D direction);

	/**
	 * Returns the point in space where the ray originates.
	 */
	Vector3D GetOrigin();

	/**
	 * Returns the unit vector of the direction the ray is pointing.
	 */
	Vector3D GetDirection();

	/**
	 * Returns the point along the ray at distance <code>distance</code>
	 * from the origin.
	 */
	Vector3D Follow(double distance);

private:
	Vector3D origin;
	Vector3D direction;
};

#endif
