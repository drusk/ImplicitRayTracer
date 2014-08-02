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
    
    int insideCount = 0;
    int outsideCount = 0;
    
    for (std::size_t i = 0; i < corners.size(); i++) {
        double fieldValue = surface->ImplicitFunction(corners[i]);
        
        if (fieldValue < 0) {
            insideCount++;
        } else if (fieldValue > 0) {
            outsideCount++;
        }
    }
    
    return insideCount > 0 && outsideCount > 0;
}