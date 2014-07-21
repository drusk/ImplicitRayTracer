#include "ray.h"

#include "gtest/gtest.h"

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
