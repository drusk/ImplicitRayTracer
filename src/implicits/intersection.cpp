#include "implicits/intersection.h"

#include <cmath>

#include <algorithm>

#include "defaults.h"
#include "implicits/spaceprune.h"

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

ImplicitRayIntersecter::ImplicitRayIntersecter(
        ImplicitSurface *implicitSurface)
    : implicitSurface(implicitSurface)
{
    SpacePruner pruner(implicitSurface);
    octree = pruner.Prune(defaults::OCTREE_PRUNING_LEVEL);
}

ImplicitRayIntersecter::ImplicitRayIntersecter(
        ImplicitSurface *implicitSurface, Octree *octree)
    : implicitSurface(implicitSurface), octree(octree)
{
}

ImplicitRayIntersecter::~ImplicitRayIntersecter()
{
    delete implicitSurface;
}

bool ImplicitRayIntersecter::Intersect(Ray ray, double *distance)
{
    std::vector<BoxIntersection> candidates = FindCandidateBoxes(ray);
    
    for (std::size_t i = 0; i < candidates.size(); i++) {
        if (FindSurfaceIntersection(candidates[i], distance)) {
            return true;
        }
    }
    
    return false;
}

std::vector<BoxIntersection> ImplicitRayIntersecter::FindCandidateBoxes(Ray &ray)
{
    std::vector<BoxIntersection> candidates;
    
    RecursivelyFindCandidates(octree, ray, &candidates);
    
    std::sort(candidates.begin(), candidates.end());
    
    return candidates;
}

void ImplicitRayIntersecter::RecursivelyFindCandidates(
        Octree *currentNode, Ray &ray,
        std::vector<BoxIntersection> *candidates)
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

bool ImplicitRayIntersecter::FindSurfaceIntersection(BoxIntersection boxIntersection, 
            double *distance)
{
    Ray ray = boxIntersection.GetRay();
    double t1 = boxIntersection.GetTNear();
    double t2 = boxIntersection.GetTFar();
    
    if ((t2 - t1) < rootFinder.GetTolerance()) {
        return false;
    }
    
    double tMid = (t1 + t2) / 2;
    double halfDistance = (t2 - t1) / 2;
    
    double maxGradChange = implicitSurface->GradLipschitzConstant(
            ray, t1, t2) * halfDistance;
    
    if (abs(implicitSurface->DirectionalGradient(ray, tMid)) >= 
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
