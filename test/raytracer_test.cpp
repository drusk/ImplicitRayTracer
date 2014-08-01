#include "ray.h"
#include "raytracer.h"
#include "sphere.h"
#include "vector3d.h"

#include "gtest/gtest.h"

#define MAX_DEPTH 5
#define FOV 30
#define BACKGROUND Vector3D(0.0, 0.0, 0.0)
#define BIAS 1e-4
#define DEFAULT_SURFACE_COLOUR Vector3D(1.0, 1.0, 1.0)
#define DEFAULT_TRANSPARENCY 0.5
#define DEFAULT_REFLECTIVITY 0.5
#define DELTA 0.0000001

TEST(RayTracerTest, IntersectObjectSingleDirectHit)
{
    RayTracer raytracer(MAX_DEPTH, FOV, BACKGROUND, BIAS);

    double radius = 2.0;
    Sphere *sphere = new Sphere(Vector3D(10.0, 0.0, 0.0), radius,
            DEFAULT_SURFACE_COLOUR, DEFAULT_TRANSPARENCY,
            DEFAULT_REFLECTIVITY);

    raytracer.AddObject(sphere);

    Ray ray(Vector3D(0.0, 0.0, 0.0), Vector3D(1.0, 0.0, 0.0));
    Sphere *intersectedObject;
    double distance;

    bool hasIntersection = raytracer.IntersectObject(ray, &intersectedObject,
            &distance);

    EXPECT_TRUE(hasIntersection);

    /* Point to same thing */
    EXPECT_EQ(sphere, intersectedObject);

    EXPECT_DOUBLE_EQ(8.0, distance);
}

TEST(RayTracerTest, IntersectObjectSinglePeripheralHit)
{
    RayTracer raytracer(MAX_DEPTH, FOV, BACKGROUND, BIAS);

    double radius = 2.0;
    Sphere *sphere = new Sphere(Vector3D(10.0, 0.0, 0.0), radius,
            DEFAULT_SURFACE_COLOUR, DEFAULT_TRANSPARENCY,
            DEFAULT_REFLECTIVITY);

    raytracer.AddObject(sphere);

    Ray ray(Vector3D(0.0, 0.0, 0.0), Vector3D(10.0, 2.0, 0.0));
    Sphere *intersectedObject;
    double distance;

    bool hasIntersection = raytracer.IntersectObject(ray, &intersectedObject,
            &distance);

    EXPECT_TRUE(hasIntersection);

    /* Point to same thing */
    EXPECT_EQ(sphere, intersectedObject);

    EXPECT_NEAR(9.413574487, distance, DELTA);
}

TEST(RayTracerTest, IntersectObjectMiss)
{
    RayTracer raytracer(MAX_DEPTH, FOV, BACKGROUND, BIAS);

    double radius = 2.0;
    Sphere *sphere = new Sphere(Vector3D(10.0, 0.0, 0.0), radius,
            DEFAULT_SURFACE_COLOUR, DEFAULT_TRANSPARENCY,
            DEFAULT_REFLECTIVITY);

    raytracer.AddObject(sphere);

    Ray ray(Vector3D(0.0, 0.0, 0.0), Vector3D(10.0, 3.0, 0.0));
    Sphere *intersectedObject;
    double distance;

    bool hasIntersection = raytracer.IntersectObject(ray, &intersectedObject,
            &distance);

    EXPECT_FALSE(hasIntersection);
}

TEST(RayTracerTest, IntersectObjectMultipleHitNearest)
{
    RayTracer raytracer(MAX_DEPTH, FOV, BACKGROUND, BIAS);

    double radius = 2.0;
    Sphere *sphere = new Sphere(Vector3D(10.0, 0.0, 0.0), radius,
            DEFAULT_SURFACE_COLOUR, DEFAULT_TRANSPARENCY,
            DEFAULT_REFLECTIVITY);
    Sphere *sphere2 = new Sphere(Vector3D(20.0, 0.0, 0.0), radius,
            DEFAULT_SURFACE_COLOUR, DEFAULT_TRANSPARENCY,
            DEFAULT_REFLECTIVITY);

    raytracer.AddObject(sphere2);
    raytracer.AddObject(sphere);

    Ray ray(Vector3D(0.0, 0.0, 0.0), Vector3D(1.0, 0.0, 0.0));
    Sphere *intersectedObject;
    double distance;

    bool hasIntersection = raytracer.IntersectObject(ray, &intersectedObject,
            &distance);

    EXPECT_TRUE(hasIntersection);

    /* Point to same thing */
    EXPECT_EQ(sphere, intersectedObject);

    EXPECT_DOUBLE_EQ(8.0, distance);
}
