#include "implicits/roots.h"

#include "gtest/gtest.h"

#include "implicits/surface.h"
#include "vector3d.h"

TEST(NewtonRootFinderTest, FindIntersection)
{
    SphereSurface surface(Vector3D(0), 1);
    
    NewtonRootFinder rootFinder;
    Ray ray(Vector3D(3, 0, 0), Vector3D(-1, 0, 0));
    double guess = 0.0;
    
    double root = rootFinder.FindRoot(&surface, ray, guess);
    Vector3D rootPoint = ray.Follow(root);
    
    double delta = rootFinder.GetTolerance();
    EXPECT_NEAR(1.0, rootPoint.GetX(), delta);
    EXPECT_NEAR(0.0, rootPoint.GetY(), delta);
    EXPECT_NEAR(0.0, rootPoint.GetZ(), delta);
}
