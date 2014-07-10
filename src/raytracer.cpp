#include "raytracer.h"

RayTracer::RayTracer(int maxRayDepth)
	: spheres(), maxRayDepth(maxRayDepth)

typedef std::list<Sphere *>::iterator SphereIterator;

{
}

void RayTracer::AddObject(Sphere *sphere)
{
	spheres.push_back(sphere);
}

Vector3D RayTracer::TraceRay(Ray ray)
{
	// TODO
	return Vector3D();

bool RayTracer::IntersectObject(Ray ray, Sphere **intersectedObject,
		double *distance)
{
	bool hasIntersection = false;
	double nearestIntersection = INFINITY;

	Sphere *nearestIntersectedObject;
	for (SphereIterator it = spheres.begin(); it != spheres.end(); it++) {
		Sphere *sphere = *it;

		double nearPoint = INFINITY;
		double farPoint = INFINITY;

		if (sphere->Intersect(ray, &nearPoint, &farPoint)) {
			hasIntersection = true;

			if (nearPoint < nearestIntersection) {
				nearestIntersection = nearPoint;

				nearestIntersectedObject = sphere;
			}
		}
	}

	if (hasIntersection) {
		*distance = nearestIntersection;
		*intersectedObject = nearestIntersectedObject;
	}

	return hasIntersection;
}

Image *RayTracer::TraceImage(int width, int height)
{
	Image *image = new Image(width, height);

	// TODO

	return image;
}
