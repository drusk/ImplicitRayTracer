#include "implicits/intersection.h"

#include <algorithm>

BoxIntersection::BoxIntersection(Box box, double tNear, double tFar)
    : box(box), tNear(tNear), tFar(tFar)
{
}

Box BoxIntersection::GetBox() const
{
    return box;
}

double BoxIntersection::GetTNear() const
{
    return tNear;
}

double BoxIntersection::GetTFar() const
{
    return tFar;
}

bool BoxIntersection::operator<(const BoxIntersection &other) const
{
    return GetTNear() < other.GetTNear();
}

RayIntersecter::RayIntersecter(Octree *octree)
    : octree(octree)
{
}

std::vector<BoxIntersection> RayIntersecter::FindCandidateBoxes(Ray &ray)
{
    std::vector<BoxIntersection> candidates;
    
    RecursivelyFindCandidates(octree, ray, &candidates);
    
    std::sort(candidates.begin(), candidates.end());
    
    return candidates;
}

void RayIntersecter::RecursivelyFindCandidates(
        Octree* currentNode, Ray &ray,
        std::vector<BoxIntersection>* candidates)
{
    if (currentNode->IsRejected()) {
        return;
    }
    
    double tNear;
    double tFar;
    Box box = currentNode->GetBox();
    
    if (currentNode->IsAccepted() && 
            ray.Intersects(box, &tNear, &tFar)) {
        candidates->push_back(BoxIntersection(box, tNear, tFar));
    } else if (!currentNode->IsLeaf()) {
        for (int i = 0; i < Octree::NUM_CHILDREN; i++) {
            RecursivelyFindCandidates(currentNode->GetChild(i), ray,
                    candidates);
        }
    }
}
