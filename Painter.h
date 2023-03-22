#pragma once
#include "glut.h"
#include <cmath>
#include "Color.h"
#include "PixelCoordConverter.h"
#include "Point.h"
#include <functional>

class Painter
{
public:
	static void DrawLine(float x1, float y1, float x2, float y2, Color color);
	static void DrawAxes(float with, float height, Color color, int step = 20);
	static void DrawFunction(std::function<float(float)> func, float x1, float x2, float width, float height, Color color);
	static void DrawPoint(float x, float y, int size, Color color);
	static void DrawCircle(float x, float y, float radius, int n, Color color);
	static void FillEllipse(float x, float y, float a, float b, Color color);
	static void FillSemiCircle(float x, float y, float radius, Color color);
	static void FillTriangle(float x1, float y1, float x2, 
		float y2, float x3, float y3, Color color);
	static void FillRectangle(Point p1, Point p2, Point p3, Point p4, Color color);
	static void DrawEzhik(float x, float y);
};

