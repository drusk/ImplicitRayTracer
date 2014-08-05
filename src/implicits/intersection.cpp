#include "implicits/intersection.h"

#include <cmath>

#include <algorithm>

BoxIntersection::BoxIntersection(Box box, Ray ray, double tNear, double tFar)
    : box(box), ray(ray), tNear(tNear), tFar(tFar)
{
}

Box BoxIntersection::GetBox() const
{
    return box;
}

Ray BoxIntersection::GetRay() const
{
    return ray;
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

RayIntersecter::RayIntersecter(ImplicitSurface *implicitSurface, 
        Octree *octree)
    : implicitSurface(implicitSurface), octree(octree)
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
        candidates->push_back(BoxIntersection(box, ray, tNear, tFar));
    } else if (!currentNode->IsLeaf()) {
        for (int i = 0; i < Octree::NUM_CHILDREN; i++) {
            RecursivelyFindCandidates(currentNode->GetChild(i), ray,
                    candidates);
        }
    }
}

bool RayIntersecter::FindSurfaceIntersection(BoxIntersection boxIntersection, 
            double *distance)
{
    Ray ray = boxIntersection.GetRay();
    double t1 = boxIntersection.GetTNear();
    double t2 = boxIntersection.GetTFar();
    
    double tMid = (t1 + t2) / 2;
    double halfDistance = (t2 - t1) / 2;
    
    double maxGradChange = implicitSurface->GradLipschitzConstant(
            ray, t1, t2) * halfDistance;
    
    if (abs(implicitSurface->DirectionalGradient(ray, tMid)) <= 
            maxGradChange) {
        double F1 = implicitSurface->ImplicitFunction(ray.Follow(t1));
        double F2 = implicitSurface->ImplicitFunction(ray.Follow(t2));
        
        if (F1 * F2 < 0) {
            // Opposite signs
            *distance = rootFinder.FindRoot(implicitSurface, ray, tMid);
            return true;
        } else {
            // Same sign, no intersection
            return false;
        }
    } else {
        // Subdivide
        BoxIntersection firstInterval(boxIntersection.GetBox(), 
                boxIntersection.GetRay(), t1, tMid);
        BoxIntersection secondInterval(boxIntersection.GetBox(), 
                boxIntersection.GetRay(), tMid, t2);

        return FindSurfaceIntersection(firstInterval, distance) ||
                FindSurfaceIntersection(secondInterval, distance);
    }
}