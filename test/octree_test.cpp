#include "implicits/octree.h"

#include "gtest/gtest.h"

#include "box.h"
#include "vector3d.h"

TEST(OctreeTest, Subdivide)
{
    Box box(Vector3D(0, 0, 0), 2);
    Octree octree(box);
    
    octree.Subdivide();
    
    Octree *child = octree.GetChild(0);
    EXPECT_DOUBLE_EQ(1.0, child->GetSideLength());

    Vector3D childCenter = child->GetCenter();
    EXPECT_DOUBLE_EQ(-0.5, childCenter.GetX());
    EXPECT_DOUBLE_EQ(-0.5, childCenter.GetY());
    EXPECT_DOUBLE_EQ(-0.5, childCenter.GetZ());
}

TEST(OctreeTest, SubdivideChild)
{
    Box box(Vector3D(0, 0, 0), 2);
    Octree octree(box);
    
    octree.Subdivide();
    
    Octree *child = octree.GetChild(0);
    child->Subdivide();
    
    Octree *grandChild = child->GetChild(0);
    
    EXPECT_DOUBLE_EQ(0.5, grandChild->GetSideLength());
}

TEST(OctreeTest, SubdivideLevel2)
{
    Box box(Vector3D(0, 0, 0), 2);
    Octree octree(box);
    
    octree.Subdivide(2);
    
    Octree *child = octree.GetChild(0);
    EXPECT_DOUBLE_EQ(1.0, child->GetSideLength());

    Octree *grandChild = child->GetChild(0);
    
    EXPECT_DOUBLE_EQ(0.5, grandChild->GetSideLength());
    
    Vector3D center = grandChild->GetCenter();
    EXPECT_DOUBLE_EQ(-0.75, center.GetX());
    EXPECT_DOUBLE_EQ(-0.75, center.GetY());
    EXPECT_DOUBLE_EQ(-0.75, center.GetZ());
}
