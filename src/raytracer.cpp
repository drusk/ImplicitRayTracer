#include "raytracer.h"

#include <cmath>
#include <cstddef>

RayTracer::RayTracer(Scene &scene, int maxRayDepth, double fieldOfView,
        Vector3D backgroundColour, double bias)
    : scene(scene), maxRayDepth(maxRayDepth), fieldOfView(fieldOfView),
      backgroundColour(backgroundColour), bias(bias)
{
}

Vector3D RayTracer::TraceRay(Ray ray, int depth)
{
    double nearestIntersection = INFINITY;
    Sphere *intersectedObject;

    bool hasIntersection = IntersectObject(ray, &intersectedObject,
            &nearestIntersection);

    if (!hasIntersection) {
        return backgroundColour;
    }

    Vector3D surfaceColour;

    Vector3D pointOfIntersection = ray.Follow(nearestIntersection);
    Vector3D intersectionNormal = intersectedObject->GetNormal(
            pointOfIntersection);

    bool inside = false;
    if (ray.GetDirection().DotProduct(intersectionNormal) > 0) {
        /* The normal and viewing direction are the same, meaning we are
         * inside the object.  Reverse the normal's sign.
         */
        inside = true;
        intersectionNormal.Reverse();
    }

    if (intersectedObject->IsTransparentOrReflective() &&
            depth < maxRayDepth) {
        double fresnelEffect = CalculateFresnelEffect(ray, intersectionNormal);

        Ray reflectedRay = CalculateReflectedRay(ray, pointOfIntersection,
                        intersectionNormal);

        Vector3D reflection = TraceRay(reflectedRay, depth + 1);
        Vector3D refraction;

        if (intersectedObject->IsTransparent()) {
            /* Also compute refraction ray from transmission. */
            Ray *refractedRay = CalculateRefractedRay(ray, inside,
                    pointOfIntersection, intersectionNormal);

            if (refractedRay != NULL) {
                refraction = TraceRay(*refractedRay, depth + 1);
            }
            
            delete refractedRay;
        }

        surfaceColour = intersectedObject->CalculateEffectiveSurfaceColour(
                reflection, refraction, fresnelEffect);
    } else {
        surfaceColour += CalculateIlluminationFromLightSources(
                intersectedObject, pointOfIntersection, intersectionNormal);
    }

    return surfaceColour + intersectedObject->GetEmissionColour();
}

bool RayTracer::IntersectObject(Ray ray, Sphere **intersectedObject,
		double *distance)
{
    bool hasIntersection = false;
    double nearestIntersection = INFINITY;

    Sphere *nearestIntersectedObject;
    for (SphereIterator it = scene.begin(); it != scene.end(); it++) {
        Sphere *sphere = *it;

        double distance = INFINITY;

        if (sphere->Intersect(ray, &distance)) {
            hasIntersection = true;

            if (distance < nearestIntersection) {
                nearestIntersection = distance;
                nearestIntersectedObject = sphere;
            }
        }
    }

    if (hasIntersection) {
        *distance = nearestIntersection;
        *intersectedObject = nearestIntersectedObject;
    }

    return hasIntersection;
}

Ray RayTracer::CalculateReflectedRay(Ray ray, Vector3D intersectionPoint,
		Vector3D normal)
{
    Vector3D rayDirection = ray.GetDirection();

    Vector3D reflectedDirection = rayDirection -
            normal * 2 * rayDirection.DotProduct(normal);

    return Ray(intersectionPoint + normal * bias, reflectedDirection);
}

/* See http://steve.hollasch.net/cgindex/render/refraction.txt */
Ray *RayTracer::CalculateRefractedRay(Ray ray, bool inside,
        Vector3D intersectionPoint, Vector3D normal)
{
    Vector3D rayDirection = ray.GetDirection();

    double ior = 1.1;
    double eta = inside ? ior : 1 / ior;
    double cosi = -(normal.DotProduct(rayDirection));

    double k = 1 - eta * eta * (1 - cosi * cosi);
    
    if (k < 0) {
        /* Total internal reflection */
        return NULL;
    }

    Vector3D refractionDirection = rayDirection * eta +
            normal * (eta * cosi - sqrt(k));

    return new Ray(intersectionPoint - normal * bias, refractionDirection);
}

Vector3D RayTracer::CalculateIlluminationFromLightSources(
        Sphere *intersectedObject, Vector3D intersectionPoint, Vector3D normal)
{
    Vector3D colour;

    for (SphereIterator it = scene.begin(); it != scene.end(); it++) {
        Sphere *sphere = *it;

        if (sphere->IsLightSource()) {
            Vector3D transmission(1.0, 1.0, 1.0);
            Vector3D lightDirection = sphere->GetCenter() - intersectionPoint;
            lightDirection.Normalize();

            for (SphereIterator it2 = scene.begin(); it2 != scene.end(); it2++) {
                Sphere *otherSphere = *it2;

                if (otherSphere == sphere) {
                    continue;
                }

                double distance;

                if (otherSphere->Intersect(
                        Ray(intersectionPoint + normal * bias, lightDirection),
                        &distance)) {
                    transmission = Vector3D(0.0, 0.0, 0.0);
                    break;
                }
            }

            colour += intersectedObject->GetSurfaceColour() * transmission *
                    std::max(0.0, normal.DotProduct(lightDirection)) *
                    sphere->GetEmissionColour();
        }
    }

    return colour;
}

Image *RayTracer::TraceImage(int width, int height)
{
    Image *image = new Image(width, height);

    Vector3D origin(0.0, 0.0, 0.0);

    double invWidth = 1 / (double) width;
    double invHeight = 1 / (double) height;
    double aspectRatio = (double) width / (double) height;
    double angle = tan(M_PI * 0.5 * fieldOfView / 180.0);
    double numPixels = width * height;

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            double rayDirX = (2 * ((x + 0.5) * invWidth) - 1) *	angle *
                    aspectRatio;
            double rayDirY = (1 - 2 * ((y + 0.5) * invHeight)) * angle;

            Vector3D rayDirection = Vector3D(rayDirX, rayDirY, -1);

            Ray ray(origin, rayDirection);
            image->SetPixel(x, y, TraceRay(ray, 0));
        }
        
        progressBar.Update((double) (y + 1) * width / numPixels);
    }
    
    progressBar.Done();

    return image;
}

double RayTracer::CalculateFresnelEffect(const Ray &ray, const Vector3D &normal)
{
    double ratioFacingRay = -(ray.GetDirection().DotProduct(normal));

    return Mix(pow(1.0 - ratioFacingRay, 3), 1, 0.1);
}

double RayTracer::Mix(double a, double b, double mix)
{
    return b * mix + a * (1.0 - mix);
}
