#include "raytracer.h"

#include "gtest/gtest.h"

#include "ray.h"
#include "scene.h"
#include "sphere.h"
#include "vector3d.h"

namespace
{
    int MAX_DEPTH = 1;
    double FOV = 30.0;
    Vector3D BACKGROUND(0.0, 0.0, 0.0);
    double BIAS = 1e-4;
    Vector3D DEFAULT_SURFACE_COLOUR(1.0, 1.0, 1.0);
    double DEFAULT_TRANSPARENCY = 0.5;
    double DEFAULT_REFLECTIVITY = 0.5;
    Vector3D DEFAULT_EMISSION_COLOUR(3.0, 3.0, 3.0);
    double DELTA = 0.0000001;
}

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

/** 
 * This is a regression test, and provides the expected values for
 * testing with implicits. 
 */
TEST(RayTracerIntegrationTest, TraceRayGeometricIntersecterRegression)
{
    Scene scene;
    scene.AddSphere(Vector3D(10, 0, 0), 4, 
            Vector3D(0.3, 0.6, 0.0), 1.0, 0.5);
    scene.AddLight(Vector3D(0.0, 5.0, 0.0), 1,
            DEFAULT_SURFACE_COLOUR, DEFAULT_TRANSPARENCY,
            DEFAULT_REFLECTIVITY,
            DEFAULT_EMISSION_COLOUR);
    
    RayTracer raytracer(scene, MAX_DEPTH, FOV, Vector3D(2.0), BIAS);

    Ray ray(Vector3D(0.0, 0.0, 0.0), Vector3D(1.0, 0.0, 0.0));
    
    Vector3D colour = raytracer.TraceRay(ray, 0);
    EXPECT_NEAR(0.059999999999999998, colour.GetX(), DELTA);
    EXPECT_NEAR(0.12, colour.GetY(), DELTA);
    EXPECT_NEAR(0.0, colour.GetZ(), DELTA);
}

/** 
 * Should get the same answer as without using implicits.
 */
TEST(RayTracerIntegrationTest, TraceRayImplicitIntersecter)
{
    Scene scene;
    scene.AddSphere(Vector3D(10, 0, 0), 4, 
            Vector3D(0.3, 0.6, 0.0), 1.0, 0.5, true);
    scene.AddLight(Vector3D(0.0, 5.0, 0.0), 1,
            DEFAULT_SURFACE_COLOUR, DEFAULT_TRANSPARENCY,
            DEFAULT_REFLECTIVITY,
            DEFAULT_EMISSION_COLOUR, true);
    
    RayTracer raytracer(scene, MAX_DEPTH, FOV, Vector3D(2.0), BIAS);

    Ray ray(Vector3D(0.0, 0.0, 0.0), Vector3D(1.0, 0.0, 0.0));
    
    Vector3D colour = raytracer.TraceRay(ray, 0);
    EXPECT_NEAR(0.059999999999999998, colour.GetX(), DELTA);
    EXPECT_NEAR(0.12, colour.GetY(), DELTA);
    EXPECT_NEAR(0.0, colour.GetZ(), DELTA);
}

TEST(RayTracerIntegrationTest, FloorSphere)
{
    bool implicit = true;
    
    Scene scene;
    scene.AddSphere(Vector3D(0, -10004, -20), 10000, 
            Vector3D(0.2, 0.2, 0.2), 0.0, 0.0, implicit);

    scene.AddLight(Vector3D(0, 20, -30), 3, Vector3D(0.0, 0.0, 0.0), 0.0, 0.0,
            Vector3D(3.0, 3.0, 3.0), implicit);
    
    RayTracer raytracer(scene, MAX_DEPTH, FOV, Vector3D(2.0), BIAS);
    Ray ray(Vector3D(0.0, 0.0, 0.0), Vector3D(0.0, -0.5, -1.0));
    
    double delta = 0.01;
    Vector3D colour = raytracer.TraceRay(ray, 0);
    EXPECT_NEAR(colour.GetX(), 0.441999, delta);
    EXPECT_NEAR(colour.GetY(), 0.441999, delta);
    EXPECT_NEAR(colour.GetZ(), 0.441999, delta);
}

TEST(RayTracerIntegrationTest, IntersectEdge)
{
    bool implicit = true;
    
    Scene scene;
    scene.AddSphere(Vector3D(0, -10004, -20), 10000, 
            Vector3D(0.2, 0.2, 0.2), 0.0, 0.0, implicit);
    scene.AddSphere(Vector3D(0, 0.5, -20), 4,
            Vector3D(0.3, 0.6, 0.0), 1.0, 0.5, implicit);
    scene.AddSphere(Vector3D(5, -1, -15), 2,
            Vector3D(1.00, 0.84, 0.0), 1.0, 0.0, implicit);
    scene.AddSphere(Vector3D(5, 0.5, -25), 3,
            Vector3D(0.53, 0.81, 0.92), 1.0, 0.0, implicit);
    scene.AddSphere(Vector3D(-5.5, -0.5, -15), 3,
            Vector3D(0.90, 0.90, 0.90), 1.0, 0.0, implicit);

    scene.AddLight(Vector3D(0, 20, -30), 3, Vector3D(0.0, 0.0, 0.0), 0.0, 0.0,
            Vector3D(3.0, 3.0, 3.0), implicit);
    
    RayTracer raytracer(scene, MAX_DEPTH, FOV, Vector3D(2.0), BIAS);
    Ray ray(Vector3D(0), Vector3D(0.00279114, -0.0485658, -1));
    
    double delta = 0.01;
    Vector3D colour = raytracer.TraceRay(ray, 0);
    
    EXPECT_NEAR(colour.GetX(), 0.0, delta);
    EXPECT_NEAR(colour.GetY(), 0.0, delta);
    EXPECT_NEAR(colour.GetZ(), 0.0, delta);
}
