#include "implicits/box.h"

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
