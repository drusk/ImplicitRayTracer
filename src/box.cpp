#include "box.h"

Box::Box(Vector3D center, double sideLength)
    : center(center), sideLength(sideLength)
{
}

Vector3D Box::GetCenter()
{
    return center;
}

double Box::GetSideLength()
{
    return sideLength;
}

std::vector<Vector3D> Box::GetCornerPoints()
{
    std::vector<Vector3D> corners;
    
    double halfLength = sideLength / 2;
    
    for (int i = -1; i <= 1; i = i + 2) {
        for (int j = -1; j <= 1; j = j + 2) {
            for (int k = -1; k <= 1; k = k + 2) {
                corners.push_back(
                        Vector3D(center.GetX() + i * halfLength,
                                center.GetY() + j * halfLength,
                                center.GetZ() + k * halfLength));
            }
        }
    }
    
    return corners;
}

Vector3D Box::GetMinPoint()
{
    double halfLength = sideLength / 2;
    return Vector3D(center.GetX() - halfLength, center.GetY() - halfLength, 
            center.GetZ() - halfLength);
}

Vector3D Box::GetMaxPoint()
{
    double halfLength = sideLength / 2;
    return Vector3D(center.GetX() + halfLength, center.GetY() + halfLength, 
            center.GetZ() + halfLength);
}
