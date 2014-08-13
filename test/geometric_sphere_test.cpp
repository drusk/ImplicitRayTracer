#include "intersecter.h"

#include "gtest/gtest.h"

#include "ray.h"
#include "vector3d.h"

TEST(GeometricRayIntersecter, RayFromOutside)
{
    GeometricRayIntersecter intersecter(Vector3D(10, 0, 0), 4);
    Ray ray(Vector3D(0), Vector3D(1, 0, 0));
    
    double distance;
    EXPECT_TRUE(intersecter.Intersect(ray, &distance));
    
    EXPECT_DOUBLE_EQ(6.0, distance);
}

TEST(GeometricRayIntersecter, RayFromInside)
{
    GeometricRayIntersecter intersecter(Vector3D(10, 0, 0), 4);
    Ray ray(Vector3D(6.1, 0, 0), Vector3D(1, 0, 0));
    
    double distance;
    EXPECT_TRUE(intersecter.Intersect(ray, &distance));
    
    EXPECT_DOUBLE_EQ(7.9, distance);
}
