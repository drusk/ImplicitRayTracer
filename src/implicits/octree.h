#ifndef OCTREE_H
#define	OCTREE_H

#include "implicits/box.h"
#include "vector3d.h"

static const int NUM_CHILDREN = 8;

class Octree {
public:
    /**
     * Constructs a new octree centered at the origin and with half
     * width/height/depth as defined by the halfDimension vector.
     */
    Octree(Box box);
    
    /**
     * Recursively frees the octree.
     */
    ~Octree();

    /**
     * Subdivides the octree into 8 subtrees.
     */
    void Subdivide();
    
    /**
     * Subdivides the octree into 8 subtrees with the number of recursive
     * levels specified by the level parameter.  For example, if level is 2,
     * the box is divided into 8, and then each of these 8 is subdivided, for
     * a total of 64 subtrees. 
     * Level must be >= 0.
     */
    void Subdivide(int level);
    
    /**
     * Returns the subtree at the specified index.
     */
    Octree *GetChild(int index);
    
    /**
     * Accept this node as being part of the implicit surface.
     */
    void Accept();
    
    /**
     * Returns true if this node has been accepted.
     */
    bool IsAccepted();
    
    /**
     * Returns the center point of the box for this subtree.
     */
    Vector3D GetCenter();
    
    /**
     * Returns the side length of the box formed by this tree.
     */
    double GetSideLength();
    
private:
    Box box;
    bool accepted;

    Vector3D halfDimension;
    
    Octree *children[8];
};

#endif