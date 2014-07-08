#ifndef RENDERER_H_
#define RENDERER_H_

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
	PPMWriter(char *outputFilename);

	/**
	 * Writes the specified image to the output file.
	 */
	void WriteImage(Image *image);

private:
	char *outputFilename;
};

#endif
