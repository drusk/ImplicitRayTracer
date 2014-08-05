#include "implicits/surface.h"

#include "gtest/gtest.h"

#include <cmath>

#include "ray.h"
#include "vector3d.h"

TEST(ImplicitSphereTest, ImplicitFunctionInside)
{
    ImplicitSphere sphere(Vector3D(1, 1, 1), 2);
    
    EXPECT_TRUE(sphere.ImplicitFunction(Vector3D(0, 0, 0)) < 0);
}

TEST(ImplicitSphereTest, ImplicitFunctionOutside)
{
    ImplicitSphere sphere(Vector3D(1, 1, 1), 2);
    
    EXPECT_TRUE(sphere.ImplicitFunction(Vector3D(3, 3, 3)) > 0);
}

TEST(ImplicitSphereTest, ImplicitFunctionBorder)
{
    ImplicitSphere sphere(Vector3D(1, 1, 1), 2);
    
    EXPECT_DOUBLE_EQ(0.0, sphere.ImplicitFunction(Vector3D(1, 1, 3)));
}

TEST(ImplicitSphereTest, BoundingBox)
{
    ImplicitSphere sphere(Vector3D(1, 1, 1), 2);
    
    Box box = sphere.BoundingBox();
    
    Vector3D center = box.GetCenter();
    EXPECT_DOUBLE_EQ(1.0, center.GetX());
    EXPECT_DOUBLE_EQ(1.0, center.GetY());
    EXPECT_DOUBLE_EQ(1.0, center.GetZ());
    
    EXPECT_TRUE(box.GetSideLength() > 4.0);
}

TEST(ImplicitSphereTest, Lipschitz)
{
    ImplicitSphere sphere(Vector3D(1, 1, 1), 2);
    Vector3D minPoint(-1, -1, -1);
    Vector3D maxPoint(3, 3, 3);
    
    EXPECT_DOUBLE_EQ(sqrt(27), sphere.LipschitzConstant(minPoint, maxPoint));
}

TEST(ImplicitSphereTest, LipschitzGrad)
{
    ImplicitSphere sphere(Vector3D(1, 1, 1), 2);
    Ray ray(Vector3D(-5, -5, -5), Vector3D(1, 1, 1));
    
    EXPECT_DOUBLE_EQ(1.0, sphere.GradLipschitzConstant(ray, 0, 1));
}

TEST(ImplicitSphereTest, Gradient)
{
    ImplicitSphere sphere(Vector3D(1, 2, 1), 2);
    
    Vector3D grad = sphere.Gradient(Vector3D(2, 1, 3));
    EXPECT_DOUBLE_EQ(2.0, grad.GetX());
    EXPECT_DOUBLE_EQ(-2.0, grad.GetY());
    EXPECT_DOUBLE_EQ(4.0, grad.GetZ());
}
