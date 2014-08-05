#include "implicits/roots.h"

#include <cmath>

NewtonRootFinder::NewtonRootFinder(double tolerance)
    : tolerance(tolerance)
{
}

double NewtonRootFinder::FindRoot(ImplicitSurface *surface, Ray ray, 
        double guess)
{
    double nextGuess = RefineGuess(surface, ray, guess);
    
    int i = 0;
    while (std::abs(nextGuess - guess) > tolerance) {
        guess = nextGuess;
        nextGuess = RefineGuess(surface, ray, nextGuess);
        i++;
    }
    
    return nextGuess;
}

double NewtonRootFinder::RefineGuess(ImplicitSurface *surface, Ray ray, 
        double guess)
{
    return guess - 
            surface->ImplicitFunction(ray.Follow(guess)) / 
            surface->DirectionalGradient(ray, guess);
}
