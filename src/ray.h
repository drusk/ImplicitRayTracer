#ifndef RAY_H_
#define RAY_H_

#include "box.h"
#include "vector3d.h"

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
	Vector3D GetOrigin() const;

	/**
	 * Returns the unit vector of the direction the ray is pointing.
	 */
	Vector3D GetDirection() const;

	/**
	 * Returns the point along the ray at distance <code>distance</code>
	 * from the origin.
	 */
	Vector3D Follow(double distance) const;

    /**
     * Returns true if this ray intersects the given box.  If there is
     * an intersection, the distances to the intersection points (along
     * the ray) are returned in tNear and tFar.
     */
    bool Intersects(Box &box, double *tNear, double *tFar);
    
private:
	Vector3D origin;
	Vector3D direction;
};

#endif
