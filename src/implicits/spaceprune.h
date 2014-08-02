#ifndef SPACEPRUNE_H
#define	SPACEPRUNE_H

#include "implicits/octree.h"
#include "implicits/surface.h"

class SpacePruner
{
public:
    SpacePruner(ImplicitSurface *surface);
    
    /**
     * Subdivide the bounding box of the implicit surface to the specified
     * level, return an octree indicating which sub-trees contain part of the
     * surface.
     */
    Octree *Prune(int level);

    /**
     * Returns true if the box has at least one corner inside and one 
     * corner outside the implicit surface.
     */
    bool IsStraddling(Box box);
    
private:
    ImplicitSurface *surface;
};

#endif
