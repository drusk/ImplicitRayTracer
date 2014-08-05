#include "ray.h"

#include "gtest/gtest.h"

#include <cmath>

#include "box.h"
#include "vector3d.h"

#define DELTA 0.0000001

TEST(RayTest, GetDirectionIsNormalized)
{
    Ray ray(Vector3D(0.0, 0.0, 0.0), Vector3D(10.0, 2.0, 0.0));

    Vector3D direction = ray.GetDirection();

    EXPECT_NEAR(0.9805806757, direction.GetX(), DELTA);
    EXPECT_NEAR(0.1961161351, direction.GetY(), DELTA);
    EXPECT_NEAR(0.0, direction.GetZ(), DELTA);
}

TEST(RayTest, FollowFromOrigin)
{
    Ray ray(Vector3D(0.0, 0.0, 0.0), Vector3D(10.0, 2.0, 0.0));

    Vector3D point = ray.Follow(10);

    EXPECT_NEAR(9.805806757, point.GetX(), DELTA);
    EXPECT_NEAR(1.961161351, point.GetY(), DELTA);
    EXPECT_NEAR(0.0, point.GetZ(), DELTA);
}

TEST(RayTest, FollowFromBehindOrigin)
{
    Ray ray(Vector3D(-1.0, 0.0, 0.0), Vector3D(10.0, 2.0, 0.0));

    Vector3D point = ray.Follow(10);

    EXPECT_NEAR(8.805806757, point.GetX(), DELTA);
    EXPECT_NEAR(1.961161351, point.GetY(), DELTA);
    EXPECT_NEAR(0.0, point.GetZ(), DELTA);
}

TEST(RayTest, Intersects)
{
    Box box(Vector3D(0), 2);
    Ray ray(Vector3D(-5, 0, 0), Vector3D(1, 0, 0));
 
    double tNear;
    double tFar;
    
    EXPECT_TRUE(ray.Intersects(box, &tNear, &tFar));
    EXPECT_DOUBLE_EQ(4, tNear);
    EXPECT_DOUBLE_EQ(6, tFar);
}

TEST(RayTest, NoIntersect)
{
    Box box(Vector3D(0), 2);
    Ray ray(Vector3D(-5, -5, 0), Vector3D(1, 0, 0));

    double tNear;
    double tFar;

    EXPECT_FALSE(ray.Intersects(box, &tNear, &tFar));
}

TEST(RayTest, IntersectsAtAngle)
{
    Box box(Vector3D(0), 2);
    Ray ray(Vector3D(2, -1, 0), Vector3D(-1, 1, 0));
    
    double tNear;
    double tFar;
    
    EXPECT_TRUE(ray.Intersects(box, &tNear, &tFar));
    EXPECT_DOUBLE_EQ(sqrt(2), tNear);
    EXPECT_DOUBLE_EQ(2 * sqrt(2), tFar);
}
