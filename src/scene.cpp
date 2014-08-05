#include "scene.h"

Scene::~Scene()
{
    while(!spheres.empty()) {
        delete spheres.front();
        spheres.pop_front();
    }
}

Sphere *Scene::AddSphere(Vector3D center, double radius, 
        Vector3D surfaceColour, double reflectivity, double transparency,
        bool implicit)
{
    Sphere *sphere = new Sphere(center, radius, surfaceColour, 
            reflectivity, transparency, implicit);
    spheres.push_back(sphere);
    
    return sphere;
}

Sphere *Scene::AddLight(Vector3D center, double radius, Vector3D surfaceColour, 
        double reflectivity, double transparency, Vector3D emissionColour,
        bool implicit)
{
    Sphere *light = new Sphere(center, radius, surfaceColour, 
            reflectivity, transparency, implicit);
    light->SetEmissionColour(emissionColour);
    
    spheres.push_back(light);
    
    return light;
}

std::list<Sphere *> Scene::GetObjects()
{
    return spheres;
}

SphereIterator Scene::begin()
{
    return spheres.begin();
}

SphereIterator Scene::end()
{
    return spheres.end();
}
