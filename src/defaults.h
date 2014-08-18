#ifndef DEFAULTS_H
#define	DEFAULTS_H

#include <string>

namespace defaults
{
    const int IMAGE_WIDTH = 640;
    const int IMAGE_HEIGHT = 480;

    const int MAX_RAY_DEPTH = 1;
    const double FIELD_OF_VIEW = 30.0;
    const double BIAS = 1e-4;
    
    const Vector3D BACKGROUND_COLOUR(2.0, 2.0, 2.0);

    const std::string OUTPUT_FILENAME = "output.ppm";
    
    const int OCTREE_SUBDIVISION_LEVEL = 0;
    
    const bool IMPLICIT = true;
}

#endif
