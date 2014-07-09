#ifndef RAYTRACER_H_
#define RAYTRACER_H_

#include <list>

#include "image.h"
#include "ray.h"
#include "sphere.h"

class RayTracer
{
public:
	/**
	 * Creates the raytracer with the specified max ray depth.
	 */
	RayTracer(int maxRayDepth);

	/**
	 * Adds an object to the scene.
	 */
	void AddObject(Sphere *sphere);

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
	 * Trace all of the rays for the scene and return an image.
	 */
	Image *TraceImage(int width, int height);

private:
	std::list<Sphere *> spheres;

	int maxRayDepth;
};

#endif
