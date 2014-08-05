#ifndef SCENE_H
#define	SCENE_H

#include <list>

#include "sphere.h"
#include "vector3d.h"

typedef std::list<Sphere *>::iterator SphereIterator;

class Scene {
public:
    ~Scene();
    
    Sphere *AddSphere(Vector3D center, double radius, Vector3D surfaceColour,
        double reflectivity, double transparency);
    
    Sphere *AddLight(Vector3D center, double radius, Vector3D surfaceColour,
        double reflectivity, double transparency, Vector3D emissionColour);

    std::list<Sphere *> GetObjects();
    
    SphereIterator begin();
    
    SphereIterator end();
    
private:
	std::list<Sphere *> spheres;
};



#endif
