#include "implicits/spaceprune.h"

#include "gtest/gtest.h"

#include "implicits/octree.h"
#include "implicits/surface.h"
#include "vector3d.h"

class TestSurface : public SphereSurface
{
public:
    TestSurface()
        : SphereSurface(Vector3D(0, 0, 0.75), 0.5)
    {
    }

    virtual Box BoundingBox()
    {
        return Box(Vector3D(0, 0, 0), 3);
    }
};


TEST(SpacePrunerTest, IsStraddling)
{
    TestSurface surface;
    SpacePruner pruner(&surface);
    
    Box box(Vector3D(-0.25, 0.0, 1.0), 0.5);
    EXPECT_TRUE(pruner.IsStraddling(box));
}

TEST(SpacePrunerTest, IsNotStraddlingInside)
{
    TestSurface surface;
    SpacePruner pruner(&surface);
    
    Box box(Vector3D(0, 0, 0.75), 0.1); 
    EXPECT_FALSE(pruner.IsStraddling(box));
}

TEST(SpacePrunerTest, IsNotStraddlingOutside)
{
    TestSurface surface;
    SpacePruner pruner(&surface);
    
    Box box(Vector3D(1.0, 1.0, 0.5), 0.1);
    EXPECT_FALSE(pruner.IsStraddling(box));
}

//TEST(SpacePrunerTest, PruneSphere)
//{
//    TestSurface surface;
//    SpacePruner pruner(&surface);
//    
//    Octree *octree = pruner.Prune(1);
//    
//    EXPECT_TRUE(octree->GetChild(0)->IsRejected());
////    Octree *child1 = octree->GetChild(1);
//    EXPECT_TRUE(octree->GetChild(2)->IsRejected());
////    Octree *child3 = octree->GetChild(3);
//    EXPECT_TRUE(octree->GetChild(4)->IsRejected());
////    Octree *child5 = octree->GetChild(5);
//    EXPECT_TRUE(octree->GetChild(6)->IsRejected());
////    Octree *child7 = octree->GetChild(7);
//
////    EXPECT_TRUE(child1->GetChild(0))
////
////    EXPECT_TRUE(octree->)
////    EXPECT_FALSE(octree->GetChild(0)->IsAccepted());
////    EXPECT_TRUE(octree->GetChild(1)->IsAccepted());
////    EXPECT_FALSE(octree->GetChild(2)->IsAccepted());
////    EXPECT_TRUE(octree->GetChild(3)->IsAccepted());
////    EXPECT_FALSE(octree->GetChild(4)->IsAccepted());
////    EXPECT_TRUE(octree->GetChild(5)->IsAccepted());
////    EXPECT_FALSE(octree->GetChild(6)->IsAccepted());
////    EXPECT_TRUE(octree->GetChild(7)->IsAccepted());
//}
