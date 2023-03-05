#pragma once
class PixelCoordConverter
{
public:
	static float xMin;
	static float xMax;
	static float yMin;
	static float yMax;

	static float width;
	static float height;

	static int MapXCoordToPixel(float x);
	static int MapYCoordToPixel(float y);

	static float MapXPixelToCoord(int x);
	static float MapYPixelToCoord(int y);

	

private:
	static float xScale();
	static float yScale();



};

