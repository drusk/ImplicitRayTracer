#include "ray.h"

#include <limits>

Ray::Ray(Vector3D origin, Vector3D direction)
    : origin(origin), direction(direction)
{
    this->direction.Normalize();
}

Vector3D Ray::GetOrigin() const
{
    return origin;
}

Vector3D Ray::GetDirection() const
{
    return direction;
}

Vector3D Ray::Follow(double distance) const
{
    return origin + direction * distance;
}

/**
 * Implemented algorithm here:
 * http://www.siggraph.org/education/materials/HyperGraph/raytrace/rtinter3.htm
 */
bool Ray::Intersects(Box &box, double *tNear, double *tFar)
{
    *tFar = std::numeric_limits<double>::infinity();
    *tNear = -*tFar;
    
    double t1;
    double t2;
    double tmp;
    
    Vector3D minPoint = box.GetMinPoint();
    Vector3D maxPoint = box.GetMaxPoint();
    
    double minX = minPoint.GetX();
    double maxX = maxPoint.GetX();
    
    double minY = minPoint.GetY();
    double maxY = maxPoint.GetY();
    
    double minZ = minPoint.GetZ();
    double maxZ = maxPoint.GetZ();
    
    // TODO: refactor to remove duplication between dimensions
    
    // Check X
    if (direction.GetX() == 0 && 
            origin.GetX() < minX && origin.GetX() > maxX) {
        return false;
    }
    
    t1 = (minX - origin.GetX()) / direction.GetX();
    t2 = (maxX - origin.GetX()) / direction.GetX();
    
    if (t1 > t2) {
        tmp = t1;
        t1 = t2;
        t2 = tmp;
    }
    
    if (t1 > *tNear) {
        *tNear = t1;
    }
    
    if (t2 < *tFar) {
        *tFar = t2;
    }
    
    if (*tNear > *tFar || *tFar < 0) {
        return false;
    }
    
    // Check Y
    if (direction.GetY() == 0 && 
            origin.GetY() < minY && origin.GetY() > maxY) {
        return false;
    }
    
    t1 = (minY - origin.GetY()) / direction.GetY();
    t2 = (maxY - origin.GetY()) / direction.GetY();
    
    if (t1 > t2) {
        tmp = t1;
        t1 = t2;
        t2 = tmp;
    }
    
    if (t1 > *tNear) {
        *tNear = t1;
    }
    
    if (t2 < *tFar) {
        *tFar = t2;
    }
    
    if (*tNear > *tFar || *tFar < 0) {
        return false;
    }
    
    // Check Z
     if (direction.GetZ() == 0 && 
            origin.GetZ() < minZ && origin.GetZ() > maxZ) {
        return false;
    }
    
    t1 = (minZ - origin.GetZ()) / direction.GetZ();
    t2 = (maxZ - origin.GetZ()) / direction.GetZ();
    
    if (t1 > t2) {
        tmp = t1;
        t1 = t2;
        t2 = tmp;
    }
    
    if (t1 > *tNear) {
        *tNear = t1;
    }
    
    if (t2 < *tFar) {
        *tFar = t2;
    }
    
    if (*tNear > *tFar || *tFar < 0) {
        return false;
    }
    
    return true;
}
