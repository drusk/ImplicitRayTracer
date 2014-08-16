#include "sphere.h"

#include "gtest/gtest.h"

#include <cmath>

#include "ray.h"
#include "vector3d.h"

namespace
{
    Vector3D DEFAULT_SURFACE_COLOUR(0);
    double DEFAULT_REFLECTIVITY = 0.5;
    double DEFAULT_TRANSPARENCY = 0.5;
    double DELTA = 0.01;
}

TEST(ImplicitSphereTest, IntersectHorizontalRayCenterOfSphere)
{
    Sphere sphere(Vector3D(0), 2, DEFAULT_SURFACE_COLOUR, 
            DEFAULT_REFLECTIVITY, DEFAULT_TRANSPARENCY, true);
    
    Ray ray(Vector3D(4, 0, 0), Vector3D(-1, 0, 0));
    
    double distance;
    EXPECT_TRUE(sphere.Intersect(ray, &distance));
    
    EXPECT_NEAR(2.0, distance, DELTA);
}

TEST(ImplicitSphereTest, IntersectDiagonalRayCenterOfSphere)
{
    Sphere sphere(Vector3D(0), 2, DEFAULT_SURFACE_COLOUR, 
            DEFAULT_REFLECTIVITY, DEFAULT_TRANSPARENCY, true);
    
    Ray ray(Vector3D(sqrt(8), -sqrt(8), 0), Vector3D(-1, 1, 0));
    
    double distance;
    EXPECT_TRUE(sphere.Intersect(ray, &distance));
    
    EXPECT_NEAR(2.0, distance, DELTA);
}

TEST(ImplicitSphereTest, NoIntersect)
{
    Sphere sphere(Vector3D(0), 2, DEFAULT_SURFACE_COLOUR, 
            DEFAULT_REFLECTIVITY, DEFAULT_TRANSPARENCY, true);
    
    Ray ray(Vector3D(1, -3, 0), Vector3D(-1, 1, 0));
    
    double distance;
    EXPECT_FALSE(sphere.Intersect(ray, &distance));
}

TEST(ImplicitSphereTest, FloorSphere)
{
    bool implicit = true;
    
    Sphere sphere(Vector3D(0, -10004, -20), 10000, 
            Vector3D(0.2, 0.2, 0.2), 0.0, 0.0, implicit);
    
    Ray ray(Vector3D(0.0, 0.0, 0.0), Vector3D(0.0, -0.5, -1.0));
    
    double distance;
    EXPECT_TRUE(sphere.Intersect(ray, &distance));
    
    double delta = 0.01;
    EXPECT_NEAR(8.9603330814670699, distance, delta);
}
