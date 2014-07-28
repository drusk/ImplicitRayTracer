#ifndef DEFAULTS_H
#define	DEFAULTS_H

namespace defaults
{
    const int IMAGE_WIDTH = 640;
    const int IMAGE_HEIGHT = 480;
    
    const int MAX_RAY_DEPTH = 5;
    const double FIELD_OF_VIEW = 30.0;
    const double BIAS = 1e-4;
    
    const Vector3D BACKGROUND_COLOUR(2.0, 2.0, 2.0);

    const std::string OUTPUT_FILENAME = "output.ppm";
}

#endif