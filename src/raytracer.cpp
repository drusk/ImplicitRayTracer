#include "raytracer.h"

RayTracer::RayTracer(int maxRayDepth)
	: spheres(), maxRayDepth(maxRayDepth)
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
}

Image *RayTracer::TraceImage(int width, int height)
{
	Image *image = new Image(width, height);

	// TODO

	return image;
}
