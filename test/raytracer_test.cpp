#include "raytracer.h"

#include "gtest/gtest.h"

#include "ray.h"
#include "scene.h"
#include "sphere.h"
#include "vector3d.h"

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
    double radius = 2.0;

    Scene scene;
    Sphere *sphere = scene.AddSphere(Vector3D(10.0, 0.0, 0.0), radius,
            DEFAULT_SURFACE_COLOUR, DEFAULT_TRANSPARENCY,
            DEFAULT_REFLECTIVITY);

    RayTracer raytracer(scene, MAX_DEPTH, FOV, BACKGROUND, BIAS);

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
    double radius = 2.0;
    
    Scene scene;
    Sphere *sphere = scene.AddSphere(Vector3D(10.0, 0.0, 0.0), radius,
            DEFAULT_SURFACE_COLOUR, DEFAULT_TRANSPARENCY,
            DEFAULT_REFLECTIVITY);
    
    RayTracer raytracer(scene, MAX_DEPTH, FOV, BACKGROUND, BIAS);

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
    double radius = 2.0;

    Scene scene;
    scene.AddSphere(Vector3D(10.0, 0.0, 0.0), radius,
            DEFAULT_SURFACE_COLOUR, DEFAULT_TRANSPARENCY,
            DEFAULT_REFLECTIVITY);
    
    RayTracer raytracer(scene, MAX_DEPTH, FOV, BACKGROUND, BIAS);

    Ray ray(Vector3D(0.0, 0.0, 0.0), Vector3D(10.0, 3.0, 0.0));
    Sphere *intersectedObject;
    double distance;

    bool hasIntersection = raytracer.IntersectObject(ray, &intersectedObject,
            &distance);

    EXPECT_FALSE(hasIntersection);
}

TEST(RayTracerTest, IntersectObjectMultipleHitNearest)
{
    double radius = 2.0;
    
    Scene scene;
    Sphere *sphere = scene.AddSphere(Vector3D(10.0, 0.0, 0.0), radius,
            DEFAULT_SURFACE_COLOUR, DEFAULT_TRANSPARENCY,
            DEFAULT_REFLECTIVITY);
    scene.AddSphere(Vector3D(20.0, 0.0, 0.0), radius,
            DEFAULT_SURFACE_COLOUR, DEFAULT_TRANSPARENCY,
            DEFAULT_REFLECTIVITY);
    
    RayTracer raytracer(scene, MAX_DEPTH, FOV, BACKGROUND, BIAS);

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
