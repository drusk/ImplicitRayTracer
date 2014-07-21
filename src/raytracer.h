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
	RayTracer(int maxRayDepth, double fieldOfView, Vector3D backgroundColour,
			double bias);
    
    /**
     * Frees objects rendered by the ray tracer after rendering is finished.
     */
    virtual ~RayTracer();
    
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
	 * The parameter depth specifies how many times we have recursed due
	 * to reflections.
	 * Returns: colour of the ray.
	 */
	Vector3D TraceRay(Ray ray, int depth);

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

	/**
	 * Returns the ray produced by the incoming ray's intersection with an
	 * object at the specified point, given that the object's surface
	 * normal is as provided.
	 */
	Ray CalculateReflectedRay(Ray ray, Vector3D intersectionPoint,
			Vector3D normal);

	/**
	 * Returns the ray produced by the incoming ray's refraction with an
	 * object at the specified point, given that the object's surface
	 * normal is as provided.  If the parameter inside is true, then the
	 * ray is refracting from inside the object, otherwise from outside.
	 */
	Ray CalculateRefractedRay(Ray ray, bool inside, Vector3D intersectionPoint,
			Vector3D normal);

	/**
	 * Calculates the light at a location on the surface of the intersected
	 * object due to anylight sources in the scene.  The parameter normal
	 * is the intersected object's surface normal at the intersection point.
	 */
	Vector3D CalculateIlluminationFromLightSources(Sphere *intersectedObject,
			Vector3D intersectionPoint, Vector3D normal);

private:
	std::list<Sphere *> spheres;

	int maxRayDepth;
	double fieldOfView;
	Vector3D backgroundColour;
	double bias;

	double CalculateFresnelEffect(const Ray &ray, const Vector3D &normal);

	double Mix(double a, double b, double mix);
};

#endif
