#include "ppmwriter.h"

#include <fstream>

PPMWriter::PPMWriter(const char *outputFilename)
	: outputFilename(outputFilename)
{
}

void PPMWriter::WriteImage(Image *image)
{
	std::ofstream ppmfile;
	ppmfile.open(outputFilename);

	/* Write header */
	ppmfile << "P6\n";
	ppmfile << image->GetWidth() << " " << image->GetHeight() << "\n";
	ppmfile << "255\n";

	/* Write image data */
	for (int y = 0; y < image->GetHeight(); y++) {
		for (int x = 0; x < image->GetWidth(); x++) {
			Vector3D pixel = image->GetPixel(x, y);
			ppmfile << FormatPixelElement(pixel.GetX());
			ppmfile << FormatPixelElement(pixel.GetY());
			ppmfile << FormatPixelElement(pixel.GetZ());
		}
	}

	ppmfile.close();
}

double PPMWriter::Clip(double value, double max)
{
	return std::min(value, max);
}

unsigned char PPMWriter::FormatPixelElement(double element)
{
	return (unsigned char)(Clip(element, 1.0) * 255);
}
