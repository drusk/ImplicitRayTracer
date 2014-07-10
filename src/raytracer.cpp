#include "raytracer.h"

#include <cmath>

typedef std::list<Sphere *>::iterator SphereIterator;

RayTracer::RayTracer(int maxRayDepth, double fieldOfView,
		Vector3D backgroundColour)
	: spheres(), maxRayDepth(maxRayDepth), fieldOfView(fieldOfView),
	  backgroundColour(backgroundColour)
{
}

void RayTracer::AddObject(Sphere *sphere)
{
	spheres.push_back(sphere);
}

Vector3D RayTracer::TraceRay(Ray ray)
{
	double nearestIntersection = INFINITY;
	Sphere *intersectedObject;

	bool hasIntersection = IntersectObject(ray, &intersectedObject,
			&nearestIntersection);

	if (!hasIntersection) {
		return backgroundColour;
	}

	Vector3D surfaceColour;

	Vector3D pointOfIntersection = ray.Follow(nearestIntersection);
	Vector3D intersectionNormal = intersectedObject->GetNormal(
			pointOfIntersection);

	// TODO

	return surfaceColour;
}

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

	Vector3D origin(0.0, 0.0, 0.0);

	double invWidth = 1 / (double) width;
	double invHeight = 1 / (double) height;
	double aspectRatio = (double) width / (double) height;
	double angle = tan(M_PI * 0.5 * fieldOfView / 180.0);

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			double rayDirX = (2 * ((x + 0.5) * invWidth) - 1) *	angle *
					aspectRatio;
			double rayDirY = (1 - 2 * ((y + 0.5) * invHeight)) * angle;

			Vector3D rayDirection = Vector3D(rayDirX, rayDirY, -1);

			Ray ray(origin, rayDirection);
			image->SetPixel(x, y, TraceRay(ray));
		}
	}

	return image;
}
