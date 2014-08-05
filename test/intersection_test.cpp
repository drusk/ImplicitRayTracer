#include "implicits/intersection.h"

#include "gtest/gtest.h"

#include <cstddef>
#include <vector>

#include "box.h"
#include "ray.h"
#include "vector3d.h"

TEST(RayIntersecterTest, FindCandidateBoxes)
{
    Box box(Vector3D(0), 2);
    Octree octree(box);
    octree.Subdivide(1);
    
    Octree *child0 = octree.GetChild(0);
    child0->Subdivide();
    
    Octree *child1 = octree.GetChild(1);
    child1->Subdivide();
    
    octree.GetChild(2)->Reject();
    octree.GetChild(3)->Reject();
    
    Octree *child4 = octree.GetChild(4);
    child4->Subdivide();

    octree.GetChild(5)->Reject();
    octree.GetChild(6)->Reject();
    octree.GetChild(7)->Reject();
    
    child0->GetChild(1)->Accept();
            
    child1->GetChild(4)->Accept();
    child4->GetChild(1)->Accept();
    child4->GetChild(4)->Accept();
    
    RayIntersecter intersecter(NULL, &octree);
    Ray ray(Vector3D(2, -0.75, -0.28), Vector3D(-1, 0, 0));
    std::vector<BoxIntersection> candidates = intersecter.FindCandidateBoxes(
            ray);
    
    EXPECT_EQ(2, candidates.size());
    
    BoxIntersection candidate0 = candidates[0];
    Vector3D candidate0Center = candidate0.GetBox().GetCenter();
    
    EXPECT_DOUBLE_EQ(0.25, candidate0Center.GetX());
    EXPECT_DOUBLE_EQ(-0.75, candidate0Center.GetY());
    EXPECT_DOUBLE_EQ(-0.25, candidate0Center.GetZ());
    EXPECT_DOUBLE_EQ(1.5, candidate0.GetTNear());
    EXPECT_DOUBLE_EQ(2.0, candidate0.GetTFar());

    BoxIntersection candidate1 = candidates[1];
    Vector3D candidate1Center = candidate1.GetBox().GetCenter();
    EXPECT_DOUBLE_EQ(-0.75, candidate1Center.GetX());
    EXPECT_DOUBLE_EQ(-0.75, candidate1Center.GetY());
    EXPECT_DOUBLE_EQ(-0.25, candidate1Center.GetZ());
    EXPECT_DOUBLE_EQ(2.5, candidate1.GetTNear());
    EXPECT_DOUBLE_EQ(3.0, candidate1.GetTFar());
}

TEST(RayIntersecterTest, FindSurfaceIntersectionOneIntersection)
{
    Box box(Vector3D(1, 0, 0), 2);
    Ray ray(Vector3D(3, 0, 0), Vector3D(-1, 0, 0));
    BoxIntersection candidate(box, ray, 1, 3);
    
    SphereSurface surface(Vector3D(0), 1);
    RayIntersecter intersecter(&surface, NULL);
    double distance;
    
    EXPECT_TRUE(intersecter.FindSurfaceIntersection(candidate, &distance));

    Vector3D intersection = ray.Follow(distance);
    EXPECT_DOUBLE_EQ(1.0, intersection.GetX());
    EXPECT_DOUBLE_EQ(0.0, intersection.GetY());
    EXPECT_DOUBLE_EQ(0.0, intersection.GetZ());
}

TEST(RayIntersecterTest, FindSurfaceIntersectionNoIntersection)
{
    Box box(Vector3D(1, 0, 0), 2);
    Ray ray(Vector3D(3, 3, 0), Vector3D(-1, 0, 0));
    BoxIntersection candidate(box, ray, 1, 3);
    
    SphereSurface surface(Vector3D(0), 1);
    RayIntersecter intersecter(&surface, NULL);
    double distance;
    
    EXPECT_FALSE(intersecter.FindSurfaceIntersection(candidate, &distance));
}
