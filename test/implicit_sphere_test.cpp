#include "sphere.h"

#include "gtest/gtest.h"

#include <cmath>

#include "ray.h"
#include "vector3d.h"

#define DEFAULT_SURFACE_COLOUR Vector3D(0)
#define DEFAULT_REFLECTIVITY 0.5
#define DEFAULT_TRANSPARENCY 0.5

TEST(ImplicitSphereTest, IntersectHorizontalRayCenterOfSphere)
{
    Sphere sphere(Vector3D(0), 2, DEFAULT_SURFACE_COLOUR, 
            DEFAULT_REFLECTIVITY, DEFAULT_TRANSPARENCY, true);
    
    Ray ray(Vector3D(4, 0, 0), Vector3D(-1, 0, 0));
    
    double distance;
    EXPECT_TRUE(sphere.Intersect(ray, &distance));
    
    EXPECT_DOUBLE_EQ(2.0, distance);
}

TEST(ImplicitSphereTest, IntersectDiagonalRayCenterOfSphere)
{
    Sphere sphere(Vector3D(0), 2, DEFAULT_SURFACE_COLOUR, 
            DEFAULT_REFLECTIVITY, DEFAULT_TRANSPARENCY, true);
    
    Ray ray(Vector3D(sqrt(8), -sqrt(8), 0), Vector3D(-1, 1, 0));
    
    double distance;
    EXPECT_TRUE(sphere.Intersect(ray, &distance));
    
    EXPECT_DOUBLE_EQ(2.0, distance);
}

TEST(ImplicitSphereTest, NoIntersect)
{
    Sphere sphere(Vector3D(0), 2, DEFAULT_SURFACE_COLOUR, 
            DEFAULT_REFLECTIVITY, DEFAULT_TRANSPARENCY, true);
    
    Ray ray(Vector3D(1, -3, 0), Vector3D(-1, 1, 0));
    
    double distance;
    EXPECT_FALSE(sphere.Intersect(ray, &distance));
}
