#ifndef INTERSECTER_H
#define	INTERSECTER_H

#include "ray.h"
#include "vector3d.h"

class RayIntersecter
{
public:
    virtual ~RayIntersecter() {};
    
    virtual bool Intersect(Ray ray, double *distance) = 0;
};

class GeometricRayIntersecter : public RayIntersecter
{
public:
    GeometricRayIntersecter(Vector3D center, double radius);
    
    virtual bool Intersect(Ray ray, double *distance);

private:
    Vector3D center;
    double radiusSquared;
};

#endif
