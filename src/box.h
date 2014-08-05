#ifndef BOX_H
#define	BOX_H

#include <vector>

#include "vector3d.h"

/**
 * An axis-aligned three-dimension "box".
 */
class Box {
public:
    /**
     * Creates a new box given the center point and side length.
     */
    Box(Vector3D center, double sideLength);

    /**
     * Returns the center point of the box.
     */
    Vector3D GetCenter();
    
    /**
     * Returns the side length of the box.
     */
    double GetSideLength();
    
    /**
     * Returns the 8 corner points of this "box".
     */
    std::vector<Vector3D> GetCornerPoints();
    
    /**
     * Returns the minimum point of this box.
     */
    Vector3D GetMinPoint();
    
    /**
     * Returns the maximum point of this box.
     */
    Vector3D GetMaxPoint();
    
private:
    Vector3D center;
    double sideLength;
};

#endif
