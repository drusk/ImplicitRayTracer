#include "image.h"

Image::Image(int width, int height)
	: width(width), height(height),
	  pixels(new Vector3D[width * height])
{
}

Image::~Image()
{
	delete[] pixels;
}

void Image::SetPixel(int x, int y, Vector3D colour)
{
	pixels[PixelIndex(x, y)] = colour;
}

Vector3D Image::GetPixel(int x, int y)
{
	return pixels[PixelIndex(x, y)];
}

int Image::PixelIndex(int x, int y)
{
	return y * width + x;
}
