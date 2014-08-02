#ifndef SURFACE_H
#define	SURFACE_H

#include "ray.h"
#include "vector3d.h"

/**
 * A surface which is defined by an implicit function.
 * See implicit function description here:
 * http://en.wikipedia.org/wiki/Implicit_function
 */
class ImplicitSurface
{
public:
    /**
     * Returns the value of the implicit function that defines this surface
     * at the specified point in space.
     */
    virtual double ImplicitFunction(Vector3D point) = 0;
    
    /**
     * Returns the Lipschitz constant for this surface in the rectangular
     * region defined by the minPoint and maxPoint.
     */
    virtual double LipschitzConstant(Vector3D minPoint, Vector3D maxPoint) = 0;

    /**
     * Returns the Gradient Lipschitz constant for this surface along the
     * specified ray, between ray distances t1 and t2.
     */
    virtual double GradLipschitzConstant(Ray ray, double t1, double t2) = 0;
};


class ImplicitSphere : public ImplicitSurface
{
public:
    ImplicitSphere(Vector3D center, double radius);
    
    virtual double ImplicitFunction(Vector3D point);
    virtual double LipschitzConstant(Vector3D minPoint, Vector3D maxPoint);
    virtual double GradLipschitzConstant(Ray ray, double t1, double t2);
    
private:
    Vector3D center;
    double radius;
};

#endif
