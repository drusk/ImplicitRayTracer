#include "implicits/roots.h"

#include "gtest/gtest.h"

#include "implicits/surface.h"
#include "vector3d.h"

TEST(NewtonRootFinderTest, FindIntersection)
{
    ImplicitSphere surface(Vector3D(0), 1);
    
    NewtonRootFinder rootFinder;
    Ray ray(Vector3D(3, 0, 0), Vector3D(-1, 0, 0));
    double guess = 0.0;
    
    double root = rootFinder.FindRoot(&surface, ray, guess);
    Vector3D rootPoint = ray.Follow(root);
    
    EXPECT_DOUBLE_EQ(1.0, rootPoint.GetX());
    EXPECT_DOUBLE_EQ(0.0, rootPoint.GetY());
    EXPECT_DOUBLE_EQ(0.0, rootPoint.GetZ());
}
