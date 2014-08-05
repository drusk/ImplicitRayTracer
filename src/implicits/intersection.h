#ifndef INTERSECTION_H
#define	INTERSECTION_H

#include <vector>

#include "box.h"
#include "implicits/octree.h"
#include "ray.h"
#include "vector3d.h"

class BoxIntersection {
public:
    BoxIntersection(Box box, double tNear, double tFar);

    Box GetBox() const;
    
    double GetTNear() const;
    
    double GetTFar() const;
    
    bool operator<(const BoxIntersection &other) const;
    
private:
    Box box;
    double tNear;
    double tFar;
};


class RayIntersecter {
public:
    /**
     * Constructs the ray intersecter for the implicit surface contained
     * in the provided octree.
     */
    RayIntersecter(Octree *octree);
    
    /**
     * Finds candidate boxes along the line of sight of the ray, in the order in
     * which they will be hit.  These are candidates for the first
     * intersection of the ray with the implicit surface.
     */
    std::vector<BoxIntersection> FindCandidateBoxes(Ray &ray);
    
private:
    Octree *octree;
    
    void RecursivelyFindCandidates(Octree *currentNode, Ray &ray,
            std::vector<BoxIntersection> *candidates);
};

#endif
