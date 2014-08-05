#ifndef INTERSECTER_H
#define	INTERSECTER_H

#include "ray.h"

class RayIntersecter {
public:
    virtual bool Intersect(Ray ray, double *distance) = 0;
};

#endif
