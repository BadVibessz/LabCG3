#include "PixelCoordConverter.h"

float PixelCoordConverter::xMin = -5.f;
float PixelCoordConverter::xMax = 5.f;

float PixelCoordConverter::yMin = -10.f;
float PixelCoordConverter::yMax = 10.f;

float PixelCoordConverter::width = 600;
float PixelCoordConverter::height = 400;

int PixelCoordConverter::MapXCoordToPixel(float x)
{
	auto xPixel = (x - xMin) * xScale();
	//.coerceIn(-1.0 * (width - 1), 2.0 * (width - 1));

	if (xPixel < -1 * width) xPixel = -1 * width;
	if (xPixel > 2 * width) xPixel = 2 * width;

	return xPixel;

		
}

int PixelCoordConverter::MapYCoordToPixel(float y)
{
	auto yPixel = (yMax - y) * yScale();
	//.coerceIn(-1.0 * (width - 1), 2.0 * (width - 1));

	if (yPixel < -1 * width) yPixel = -1 * height;
	if (yPixel > 2 * width) yPixel = 2 * height;

	return yPixel;
}

float PixelCoordConverter::MapXPixelToCoord(int x)
{
	return  x / xScale() + xMin;
}

float PixelCoordConverter::MapYPixelToCoord(int y)
{
	return  yMax - y / yScale();
}

float PixelCoordConverter::xScale()
{
	return width / (xMax - xMin);
}

float PixelCoordConverter::yScale()
{
	return height / (yMax - yMin);
}
