#ifndef SURFACE_H
#define	SURFACE_H

#include "box.h"
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
    virtual ~ImplicitSurface() {};
    
    /**
     * Returns a bounding box around this surface.  It does not have to be
     * the minimal bounding box.
     */
    virtual Box BoundingBox() = 0;
    
    /**
     * Returns the value of the implicit function that defines this surface
     * at the specified point in space.
     */
    virtual double ImplicitFunction(Vector3D point) = 0;
    
    /**
     * Returns the gradient of the implicit function that defines this 
     * surface at the specified point in space.
     */
    virtual Vector3D Gradient(Vector3D point) = 0;
    
    /**
     * Returns the gradient of the implicit function in the direction
     * of the ray, at the point t along the ray.
     */
    virtual double DirectionalGradient(Ray ray, double t) = 0;
    
    /**
     * Returns the Lipschitz constant for this surface in the
     * region defined by the minPoint and maxPoint.
     */
    virtual double LipschitzConstant(Vector3D minPoint, Vector3D maxPoint) = 0;

    /**
     * Returns the Gradient Lipschitz constant for this surface along the
     * specified ray, between ray distances t1 and t2.
     */
    virtual double GradLipschitzConstant(Ray ray, double t1, double t2) = 0;
};


class SphereSurface : public ImplicitSurface
{
public:
    SphereSurface(Vector3D center, double radius);
    
    virtual Box BoundingBox();
    virtual double ImplicitFunction(Vector3D point);
    virtual Vector3D Gradient(Vector3D point);
    virtual double DirectionalGradient(Ray ray, double t);
    virtual double LipschitzConstant(Vector3D minPoint, Vector3D maxPoint);
    virtual double GradLipschitzConstant(Ray ray, double t1, double t2);
    
private:
    Vector3D center;
    double radius;
};

#endif
