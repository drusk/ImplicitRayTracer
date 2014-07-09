#ifndef IMAGE_H_
#define IMAGE_H_

#include "vector.h"

class Image
{
public:
	/**
	 * Creates an image with the specified dimensions.
	 */
	Image(int width, int height);

	/**
	 * Destructor frees dynamic memory allocated for the image.
	 */
	~Image();

	void SetPixel(int x, int y, Vector3D colour);
	Vector3D GetPixel(int x, int y);

private:
	int width;
	int height;

	/* Stored in row-major order. */
	Vector3D *pixels;

	/**
	 * Retrieves the index in the pixel array corresponding to the
	 * specified x and y position.
	 */
	int PixelIndex(int x, int y);
};

#endif
