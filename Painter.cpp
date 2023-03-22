#include "Painter.h"

using namespace std;
void Painter::DrawLine(float x1, float y1, float x2, float y2, Color color)
{
	glColor3f(color.R, color.G, color.B);

	glBegin(GL_LINES);
	glVertex2f(x1, y1);
	glVertex2f(x2, y2);
	glEnd();

	glFlush();
}

void Painter::DrawAxes(float width, float height, Color color, int step)
{
	// arrows
	FillTriangle(width, height / 2, width - 10,
		height / 2 - 5, width - 10, height / 2 + 5, color);

	FillTriangle(width / 2, 0, width / 2 - 5, 10, width / 2 + 5, 10, color);

	// axes
	glColor3f(color.R, color.G, color.B);
	glLineWidth(1);
	DrawLine(0, height / 2, width, height / 2, color);
	DrawLine(width / 2, 0, width / 2, height, color);

	//float x0 = width / 2;
	//float y0 = height / 2;
	//
	//int size = 5;

	//int nx = width / step;
	//int ny = height / step;

	//// x axis
	//for (int i = 1; i < nx; i++)
	//{
	//	int dx = i * step;
	//	DrawLine(x0 + dx, y0 + size, x0 + dx, y0 - size, color);
	//	DrawLine(x0 - dx , y0 + size, x0 - dx, y0 - size, color);
	//}

	//// y axis
	//for (int i = 1; i < ny; i++)
	//{
	//	int dy = i * step;
	//	DrawLine( x0 + size, y0 + dy, x0 - size, y0 + dy, color);
	//	DrawLine( x0 + size, y0 - dy, x0 - size, y0 - dy, color);
	//}


	// scale

	int x0 = PixelCoordConverter::MapXCoordToPixel(0);
	int y0 = PixelCoordConverter::MapYCoordToPixel(0);

	int size = 5;
	int n = 20;

	float left = PixelCoordConverter::xMin;
	float right = PixelCoordConverter::xMax;

	float xInc = (right - left) / n;

	float i = left;
	while (i <= right - xInc)
	{
		int x = PixelCoordConverter::MapXCoordToPixel(i);
		DrawLine(x, y0 - size, x, y0 + size, color);

		i += xInc;
	}

	float bottom = PixelCoordConverter::yMin;
	float top = PixelCoordConverter::yMax;

	float yInc = (top - bottom) / n;

	i = bottom;
	while (i <= top - yInc)
	{
		int y = PixelCoordConverter::MapYCoordToPixel(i);
		DrawLine(x0 - size, y, x0 + size, y, color);
		i += yInc;

	}
}

void Painter::DrawFunction(std::function<float(float)> func, float x1, float x2,
	float width, float height, Color color)
{
	if (x1 >= x2) return;

	/*PixelCoordConverter::xMin = x1;
	PixelCoordConverter::xMax = x2;*/

	glColor3f(color.R, color.G, color.B);
	glLineWidth(2);
	glBegin(GL_LINE_STRIP);

	int i = 0;
	while (i < width)
	{
		float x = PixelCoordConverter::MapXPixelToCoord(i);
		float y = func(x);

		glVertex2f(PixelCoordConverter::MapXCoordToPixel(x),
			PixelCoordConverter::MapYCoordToPixel(y));

		i += 5;
	}
	glEnd();

}

void Painter::DrawPoint(float x, float y, int size, Color color)
{
	glPointSize(2);
	glBegin(GL_POINTS);
	glColor3f(color.R, color.G, color.B);
	glVertex2f(x, y);
	glEnd();

}

void Painter::DrawCircle(float x, float y, float radius, int n, Color color)
{

	glColor3f(color.R, color.G, color.B);
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < n; i++) {
		float alpha = 2.0f * 3.1415926f * float(i) / float(n);
		glVertex2f(x + radius * cosf(alpha), y + radius * sinf(alpha));
	}
	glEnd();

}

void Painter::FillEllipse(float x, float y, float a, float b, Color color)
{
	int i;
	int n = 100;

	GLfloat twoPi = 2.0f * 3.1415926f;
	glColor3f(color.R, color.G, color.B);
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(x, y);
	for (i = 0; i <= n; i++) {
		glVertex2f(
			x + ((a + 1) * cos(i * twoPi / n)),
			y + ((b - 1) * sin(i * twoPi / n))
		);
	}
	glEnd();

}

void Painter::FillSemiCircle(float x, float y, float radius, Color color)
{
	int i;
	int n = 100;

	GLfloat twicePi = 2.0f * 3.1415926f;
	glColor3f(color.R, color.G, color.B);
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(x, y);
	for (i = 0; i <= n / 2; i++) {
		glVertex2f(
			x + ((radius + 1) * cos(i * twicePi / n)),
			y + ((radius - 1) * sin(i * twicePi / n))
		);
	}
	glEnd();

}

void Painter::FillTriangle(float x1, float y1, float x2,
	float y2, float x3, float y3, Color color)
{
	glColor3f(color.R, color.G, color.B);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBegin(GL_TRIANGLES);
	glVertex3f(x1, y1, 0);
	glVertex3f(x2, y2, 0);
	glVertex3f(x3, y3, 0);
	glEnd();

}

void Painter::FillRectangle(Point p1, Point p2, Point p3, Point p4, Color color)
{

	glColor3f(color.R, color.G, color.B);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glBegin(GL_POLYGON);

	glVertex3f(p1.x, p1.y, 0);
	glVertex3f(p2.x, p2.y, 0);
	glVertex3f(p3.x, p3.y, 0);
	glVertex3f(p4.x, p4.y, 0);

	glEnd();

}

void Painter::DrawEzhik(float x, float y)
{

	int a = 100;
	int b = 115;

	Color baseColor = Color(201 / 255.f, 42 / 255.f, 114 / 255.f);
	Color glassesColor = Color(83 / 255.f, 26 / 255.f, 131 / 255.f);
	Color eyebrowColor = Color(116 / 255.f, 11 / 255.f, 59 / 255.f);

	float glassRad = 30;
	float eyeRad = 20;
	float pupilRad = 5;

	// hair
	FillTriangle(x - 100, y, x - 100, y - 100, x, y - 100, glassesColor);
	FillTriangle(x - 50, y - 100, x, y - 175, x + 50, y - 100, glassesColor);
	FillTriangle(x - 75, y - 100, x - 75, y - 150, x, y - 100, glassesColor);
	FillTriangle(x + 75, y - 100, x + 75, y - 150, x, y - 100, glassesColor);
	FillTriangle(x + 100, y, x + 100, y - 100, x, y - 100, glassesColor);

	// base
	FillEllipse(x, y, a, b, baseColor);

	// glasses
	FillEllipse(x - a / 3, y - b / 3, glassRad, glassRad, glassesColor);
	FillEllipse(x + a / 3, y - b / 3, glassRad, glassRad, glassesColor);

	// eyes
	FillEllipse(x - a / 3, y - b / 3, eyeRad, eyeRad, Color(1, 1, 1));
	FillEllipse(x + a / 3, y - b / 3, eyeRad, eyeRad, Color(1, 1, 1));

	// pupils
	FillEllipse(x - a / 3 + 10, y - b / 3, pupilRad, pupilRad, Color(0, 0, 0));
	FillEllipse(x + a / 3 - 10, y - b / 3, pupilRad, pupilRad, Color(0, 0, 0));

	// eyebrows
	float dx = 20;
	float dy = 32;
	float h = 7;

	auto p1 = Point(x - a / 3 - dx, y - b / 3 - dy);
	auto p2 = Point(x - a / 3 + dx, y - b / 3 - dy);
	auto p3 = Point(x - a / 3 + dx, y - b / 3 - dy - h);
	auto p4 = Point(x - a / 3 - dx, y - b / 3 - dy - h);
	FillRectangle(p1, p2, p3, p4, eyebrowColor);

	p1 = Point(x + a / 3 - dx, y - b / 3 - dy);
	p2 = Point(x + a / 3 + dx, y - b / 3 - dy);
	p3 = Point(x + a / 3 + dx, y - b / 3 - dy - h);
	p4 = Point(x + a / 3 - dx, y - b / 3 - dy - h);
	FillRectangle(p1, p2, p3, p4, eyebrowColor);


	// legs
	FillEllipse(x - a / 3, y + b, 15, 30, baseColor);
	FillEllipse(x + a / 3, y + b, 15, 30, baseColor);

	// arms
	FillEllipse(x - a, y + b / 2, 15, 30, baseColor);
	FillEllipse(x + a, y + b / 2, 15, 30, baseColor);

	// smile
	FillSemiCircle(x, y, 15, glassesColor);
}

