#include "implicits/spaceprune.h"

#include <cmath>
#include <vector>

#include "vector3d.h"

SpacePruner::SpacePruner(ImplicitSurface *surface)
    : surface(surface)
{
}

Octree *SpacePruner::Prune(int level)
{
    Octree *octree = new Octree(surface->BoundingBox());
    octree->Subdivide(level);
    
    ProcessBox(octree);
    
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

void SpacePruner::ProcessBox(Octree *tree)
{
    if (!tree->IsLeaf()) {
        for (int i = 0; i < Octree::NUM_CHILDREN; i++) {
            ProcessBox(tree->GetChild(i));
        }
    } else {
        Box box = tree->GetBox();
        
        if (IsStraddling(box)) {
            tree->Accept();
        } else {
            double lipschitzConstant = surface->LipschitzConstant(
                    box.GetMinPoint(), box.GetMaxPoint());
            
            double fieldValue = surface->ImplicitFunction(box.GetCenter());
            
            double maxDistance = (box.GetMaxPoint() - box.GetCenter()).Length();
            if (std::abs(fieldValue) > lipschitzConstant * maxDistance) {
                tree->Reject();
            } else{
                tree->Subdivide();
                
                /* After subdividing its not a leaf, so we process it again
                   and this time process the children.*/
                ProcessBox(tree);
            } 
        }
    }
}
