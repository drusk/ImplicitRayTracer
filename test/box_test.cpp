#include "box.h"

#include "gtest/gtest.h"

#include <vector>

#include "vector3d.h"

void AssertContainsPoint(std::vector<Vector3D> points, Vector3D point)
{
    bool contains = false;
    
    for (std::size_t i = 0; i < points.size(); i++) {
        Vector3D currentPoint = points[i];
        
        if (currentPoint.GetX() == point.GetX() &&
                currentPoint.GetY() == point.GetY() &&
                currentPoint.GetZ() == point.GetZ()) {
            contains = true;
            break;
        }
    }
    
    EXPECT_TRUE(contains);
}

TEST(BoxTest, GetCornerPoints)
{
    Box box(Vector3D(1, 1, 1), 2);
    
    std::vector<Vector3D> corners = box.GetCornerPoints();
    
    EXPECT_EQ(8, corners.size());
    AssertContainsPoint(corners, Vector3D(0, 0, 0));
    AssertContainsPoint(corners, Vector3D(0, 0, 2));
    AssertContainsPoint(corners, Vector3D(0, 2, 0));
    AssertContainsPoint(corners, Vector3D(0, 2, 2));
    AssertContainsPoint(corners, Vector3D(2, 0, 0));
    AssertContainsPoint(corners, Vector3D(2, 0, 2));
    AssertContainsPoint(corners, Vector3D(2, 2, 0));
    AssertContainsPoint(corners, Vector3D(2, 2, 2));
}

TEST(BoxTest, MinPoint)
{
    Box box(Vector3D(1, 1, 1), 3);
    
    Vector3D minPoint = box.GetMinPoint();
    EXPECT_DOUBLE_EQ(-0.5, minPoint.GetX());
    EXPECT_DOUBLE_EQ(-0.5, minPoint.GetY());
    EXPECT_DOUBLE_EQ(-0.5, minPoint.GetZ());
}

TEST(BoxTest, MaxPoint)
{
    Box box(Vector3D(1, 1, 1), 3);
    
    Vector3D maxPoint = box.GetMaxPoint();
    EXPECT_DOUBLE_EQ(2.5, maxPoint.GetX());
    EXPECT_DOUBLE_EQ(2.5, maxPoint.GetY());
    EXPECT_DOUBLE_EQ(2.5, maxPoint.GetZ());
}
