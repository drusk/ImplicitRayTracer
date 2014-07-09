#ifndef PPMWRITER_H_
#define PPMWRITER_H_

#include "image.h"

/**
 * Writes an image to disk in PPM file format.
 */
class PPMWriter
{
public:
	/**
	 * Creates a writer which will output to a file with the
	 * specified name.
	 */
	PPMWriter(const char *outputFilename);

	/**
	 * Writes the specified image to the output file.
	 */
	void WriteImage(Image *image);

private:
	const char *outputFilename;

	/**
	 * Clips a value so that if it is above the specified max value,
	 * the max value will be returned.
	 * Ex: Clip(1, 2) => 1, Clip(2, 1) => 1
	 */
	double Clip(double value, double max);

	/**
	 * Formats pixel data (x, y or z component) for use in PPM file.
	 */
	unsigned char FormatPixelElement(double element);
};

#endif
