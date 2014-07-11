#include "vector.h"

#include <iostream>

#include "image.h"
#include "ppmwriter.h"
#include "raytracer.h"
#include "sphere.h"
#include "vector.h"

void CreateScene(RayTracer &rayTracer)
{
	std::cout << "Creating scene..." << std::endl;

	rayTracer.AddObject(
			new Sphere(Vector3D(0, -10004, -20), 10000,
					Vector3D(0.2, 0.2, 0.2), 0.0, 0.0)
	);
	rayTracer.AddObject(
			new Sphere(Vector3D(0, 0.5, -20), 4,
					Vector3D(0.3, 0.6, 0.0), 1.0, 0.5)
	);
	rayTracer.AddObject(
			new Sphere(Vector3D(5, -1, -15), 2,
					Vector3D(1.00, 0.84, 0.0), 1.0, 0.0)
	);
	rayTracer.AddObject(
			new Sphere(Vector3D(5, 0.5, -25), 3,
					Vector3D(0.53, 0.81, 0.92), 1.0, 0.0)
	);
	rayTracer.AddObject(
			new Sphere(Vector3D(-5.5, -0.5, -15), 3,
					Vector3D(0.90, 0.90, 0.90), 1.0, 0.0)
	);

	Sphere *light = new Sphere(Vector3D(0, 20, -30), 3,
			Vector3D(0.0, 0.0, 0.0), 0.0, 0.0);
	light->SetEmissionColour(Vector3D(3.0, 3.0, 3.0));

	rayTracer.AddObject(light);
}

int main(int argc, char **argv)
{
	/* Parameters for the application.
	 * TODO: allow these to be specified on the command line or in a
	 * config file, etc.
	 */
	int maxRayDepth = 5;
	double fieldOfView = 30.0;
	int imageWidth = 640;
	int imageHeight = 480;
	Vector3D backgroundColour(2.0, 2.0, 2.0);
	double bias = 1e-4;
	std::string outputFilename = "output.ppm";

	RayTracer rayTracer(maxRayDepth, fieldOfView, backgroundColour, bias);

	CreateScene(rayTracer);

	std::cout << "Finished creating scene, tracing image..." << std::endl;

	Image *image = rayTracer.TraceImage(imageWidth, imageHeight);

	std::cout << "Finished tracing image, writing result to "
			<< outputFilename << std::endl;

	PPMWriter ppmWriter(outputFilename.c_str());
	ppmWriter.WriteImage(image);

	std::cout << "Finished writing output." << std::endl;
	std::cout << "Done." << std::endl;

	return 0;
}
