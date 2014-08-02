#include "implicits/spaceprune.h"

#include <vector>

#include "vector3d.h"

SpacePruner::SpacePruner(ImplicitSurface* surface)
    : surface(surface)
{
}

Octree *SpacePruner::Prune(int level)
{
    Octree *octree = new Octree(surface->BoundingBox());
    octree->Subdivide(level);
    
    // TODO
    
    return octree;
}

bool SpacePruner::IsStraddling(Box box)
{
    std::vector<Vector3D> corners = box.GetCornerPoints();
    
    bool hasInside = false;
    bool hasOutside = false;
    
    for (std::size_t i = 0; i < corners.size(); i++) {
        double fieldValue = surface->ImplicitFunction(corners[i]);
        
        if (fieldValue < 0) {
            hasInside = true;
        } else if (fieldValue > 0) {
            hasOutside = true;
        }
        
        if (hasInside && hasOutside) {
            return true;
        }
    }
    
    return false;
}