#ifndef INTERSECTION_H
#define	INTERSECTION_H

#include <vector>

#include "box.h"
#include "implicits/octree.h"
#include "implicits/roots.h"
#include "implicits/surface.h"
#include "ray.h"
#include "vector3d.h"

class BoxIntersection {
public:
    BoxIntersection(Box box, Ray ray, double tNear, double tFar);

    Box GetBox() const;
    
    Ray GetRay() const;
    
    double GetTNear() const;
    
    double GetTFar() const;
    
    bool operator<(const BoxIntersection &other) const;
    
private:
    Box box;
    Ray ray;
    double tNear;
    double tFar;
};


class RayIntersecter {
public:
    /**
     * Constructs the ray intersecter for the implicit surface contained
     * in the provided octree.
     */
    RayIntersecter(ImplicitSurface *implicitSurface, Octree *octree);

    /**
     * Finds the ray intersection with the implicit surface within a box that
     * the ray intersects.  Returns true if there is an intersection with
     * the implicit surface, in which case the intersection is returned
     * through the intersectionPoint parameter.
     */
    bool FindSurfaceIntersection(BoxIntersection boxIntersection, 
            Vector3D &intersectionPoint);
    
    /**
     * Finds candidate boxes along the line of sight of the ray, in the order in
     * which they will be hit.  These are candidates for the first
     * intersection of the ray with the implicit surface.
     */
    std::vector<BoxIntersection> FindCandidateBoxes(Ray &ray);
    
private:
    ImplicitSurface *implicitSurface;
    Octree *octree;
    NewtonRootFinder rootFinder;
    
    void RecursivelyFindCandidates(Octree *currentNode, Ray &ray,
            std::vector<BoxIntersection> *candidates);
};

#endif
