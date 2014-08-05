#ifndef IMPLICITINTERSECTION_H
#define	IMPLICITINTERSECTION_H

#include <vector>

#include "box.h"
#include "implicits/octree.h"
#include "implicits/roots.h"
#include "implicits/surface.h"
#include "intersecter.h"
#include "ray.h"
#include "vector3d.h"

class BoxIntersection
{
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


class ImplicitRayIntersecter : public RayIntersecter
{
public:
    /**
     * Constructs the ray intersecter for the implicit surface, first
     * building an octree.
     */
    ImplicitRayIntersecter(ImplicitSurface *implicitSurface);
    
    /**
     * Constructs the ray intersecter for the implicit surface contained
     * in the provided octree.
     */
    ImplicitRayIntersecter(ImplicitSurface *implicitSurface, Octree *octree);

    /**
	 * Computes the intersection of the ray with the implicit surface.
     * Returns true if there is an intersection, false otherwise.  
     * If there is an intersection, the distance parameter is used to
     * return the distance along the ray at which the intersection
     * occurs.
     */
    virtual bool Intersect(Ray ray, double *distance);
    
    /**
     * Finds the ray intersection with the implicit surface within a box that
     * the ray intersects.  Returns true if there is an intersection with
     * the implicit surface, in which case the distance parameter is used to
     * return the distance along the ray at which the intersection
     * occurs.
     */
    bool FindSurfaceIntersection(BoxIntersection boxIntersection, 
            double *distance);
    
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
