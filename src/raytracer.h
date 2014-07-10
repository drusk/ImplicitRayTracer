#ifndef RAYTRACER_H_
#define RAYTRACER_H_

#include <list>

#include "image.h"
#include "ray.h"
#include "sphere.h"
#include "vector.h"

class RayTracer
{
public:
	/**
	 * Creates the raytracer with the specified max ray depth and field
	 * of view (in degrees).
	 */
	RayTracer(int maxRayDepth, double fieldOfView, Vector3D backgroundColour);

	/**
	 * Adds an object to the scene.
	 */
	void AddObject(Sphere *sphere);

	/**
	 * Trace all of the rays for the scene and return an image.
	 */
	Image *TraceImage(int width, int height);

	/**
	 * Trace the specified ray.  If this ray intersects any of the
	 * objects in the scene, the intersection point and normal at the
	 * intersection point are calculated in order to determine the
	 * shading for this point.
	 * Shading is determined by the properties of the surface intersected.
	 * Returns: colour of the ray.
	 */
	Vector3D TraceRay(Ray ray);

	/**
	 * Checks to see if the ray intersects any objects.  Returns true if
	 * there is an intersection, false otherwise.  If there is an
	 * intersection, the parameter intersectedObject is used to return
	 * a reference to the intersected object, and distance is used to
	 * return the distance to the nearest intersection point.
	 *
	 * If multiple objects are intersected by the ray, the closest one
	 * is returned.
	 */
	bool IntersectObject(Ray ray, Sphere **intersectedObject, double *distance);

private:
	std::list<Sphere *> spheres;

	int maxRayDepth;
	double fieldOfView;
	Vector3D backgroundColour;
};

#endif
