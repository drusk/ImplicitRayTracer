#ifndef ROOTS_H
#define	ROOTS_H

#include "implicits/surface.h"
#include "ray.h"
#include "vector3d.h"

/**
 * Finds roots of the implicit function for an implicit surface using
 * Newton's method.
 */
class NewtonRootFinder {
public:
    /**
     * 
     */
    NewtonRootFinder(double tolerance = 0.000001);
    
    /**
     * Finds the root (zero) of the implicit function along the ray.  Begins 
     * at the distance currentGuess along the ray.
     */
    double FindRoot(ImplicitSurface *surface, Ray ray, double currentGuess);
    
private:
    double tolerance;
    
    double RefineGuess(ImplicitSurface *surface, Ray ray, double guess);
};

#endif
