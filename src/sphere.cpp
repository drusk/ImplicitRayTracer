#include "sphere.h"

#include "implicits/intersection.h"
#include "implicits/surface.h"

Sphere::Sphere(Vector3D center, double radius, Vector3D surfaceColour,
        double reflectivity, double transparency, bool implicit)
    : center(center),
      radius(radius),
      surfaceColour(surfaceColour),
      reflectivity(reflectivity),
      transparency(transparency),
      isLightSource(false)
{
    if (implicit) {
        rayIntersecter = new ImplicitRayIntersecter(
                new SphereSurface(center, radius));
    } else {
        rayIntersecter = new GeometricRayIntersecter(center, radius);
    }
}

Sphere::~Sphere()
{
    delete rayIntersecter;
}

Vector3D Sphere::GetCenter()
{
    return center;
}

Vector3D Sphere::GetSurfaceColour()
{
    return surfaceColour;
}

void Sphere::SetEmissionColour(Vector3D colour)
{
    emissionColour = colour;
    isLightSource = true;
}

Vector3D Sphere::GetEmissionColour()
{
    return emissionColour;
}

bool Sphere::IsLightSource()
{
    return isLightSource;
}

bool Sphere::Intersect(Ray ray, double *distance)
{
    return rayIntersecter->Intersect(ray, distance);
}

Vector3D Sphere::GetNormal(Vector3D intersectionPoint)
{
    Vector3D normal = intersectionPoint - center;
    normal.Normalize();
    return normal;
}

bool Sphere::IsTransparent()
{
    return transparency > 0;
}

bool Sphere::IsTransparentOrReflective()
{
    return IsTransparent() || reflectivity > 0;
}

Vector3D Sphere::CalculateEffectiveSurfaceColour(Vector3D reflection,
        Vector3D refraction, double fresnelEffect)
{
    Vector3D externalColour = reflection * fresnelEffect +
            refraction * (1 - fresnelEffect) * transparency;

    return externalColour * surfaceColour;
}
