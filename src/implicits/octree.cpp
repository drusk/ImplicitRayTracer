#include "implicits/octree.h"

#include <cstddef>
#include <stdexcept>

Octree::Octree(Box box)
    : box(box), accepted(false), rejected(false),
      halfDimension(box.GetSideLength() / 2)
{
    // Initially no children.
    for (int i = 0; i < NUM_CHILDREN; i++) {
        children[i] = NULL;
    }
}

Octree::~Octree()
{
    // Recursively delete sub-trees.
    for (int i = 0; i < NUM_CHILDREN; i++) {
        delete children[i];
    }
}

void Octree::Subdivide()
{
    double scaleFactor = 0.5;
    
    for (int i = 0; i < NUM_CHILDREN; i++) {
        Vector3D newCenter = box.GetCenter();
        newCenter += halfDimension * 
                Vector3D(i & 4 ? scaleFactor : -scaleFactor,
                         i & 2 ? scaleFactor : -scaleFactor,
                         i & 1 ? scaleFactor : -scaleFactor);
        
        children[i] = new Octree(Box(newCenter, 
                box.GetSideLength() * scaleFactor));
    }
}

void Octree::Subdivide(int level)
{
    if (level < 0) {
        throw std::range_error("Subdivision level must be >= 0.");
    }

    if (level > 0) {
        Subdivide();
        level--;

        for (int i = 0; i < NUM_CHILDREN; i++) {
            GetChild(i)->Subdivide(level);
        }
    }
}

Octree *Octree::GetChild(int index)
{
    if (index < 0 || index >= NUM_CHILDREN) {
        throw std::range_error("Child index out of range");
    }
    
    return children[index];
}

void Octree::Accept()
{
    accepted = true;
}

bool Octree::IsAccepted()
{
    return accepted;
}

void Octree::Reject()
{
    rejected = true;
}

bool Octree::IsRejected()
{
    return rejected;
}

Vector3D Octree::GetCenter()
{
    return box.GetCenter();
}

double Octree::GetSideLength()
{
    return box.GetSideLength();
}

bool Octree::IsLeaf()
{
    return children[0] == NULL;
}

Box Octree::GetBox()
{
    return box;
}
