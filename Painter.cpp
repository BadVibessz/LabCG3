#include "Painter.h"

using namespace std;
void Painter::DrawLine(float x1, float y1, float x2, float y2)
{

	glBegin(GL_LINES);
	glVertex2f(x1, y1);
	glVertex2f(x2, y2);
	glEnd();

	glFlush();

}

void Painter::DrawAxes(float width, float height, Color color)
{
	glColor3f(color.R, color.G, color.B);
	DrawLine(0, height / 2, width, height / 2);
	DrawLine(width / 2, 0, width / 2, height);
}

void Painter::DrawFunction(float(*function)(float), float x1, float x2, float width, float height, Color color)
{
	if (x1 >= x2) return;

	int i = 0;
	while (i < width)
	{
		float x = PixelCoordConverter::MapXPixelToCoord(i);
		float y = function(x);

		DrawPoint(PixelCoordConverter::MapXCoordToPixel(x),
			PixelCoordConverter::MapYCoordToPixel(y), 2, color);

		i++;
	}

}

void Painter::DrawPoint(float x, float y, int size, Color color)
{
	glPointSize(2);
	glBegin(GL_POINTS);
	glColor3f(color.R, color.G, color.B);
	/*glVertex2f(PixelCoordConverter::MapXCoordToPixel(x),
		PixelCoordConverter::MapYCoordToPixel(y));*/

		/*auto x1 = PixelCoordConverter::MapXCoordToPixel(PixelCoordConverter::MapXPixelToCoord(x));
		auto y1 = PixelCoordConverter::MapYCoordToPixel(PixelCoordConverter::MapYPixelToCoord(y));

		glVertex2f(PixelCoordConverter::MapXCoordToPixel(PixelCoordConverter::MapXPixelToCoord(x)),
			PixelCoordConverter::MapYCoordToPixel(PixelCoordConverter::MapYPixelToCoord(y)));*/
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
	int triangleAmount = 100; //# of triangles used to draw circle

	GLfloat twicePi = 2.0f * 3.1415926f;
	glColor3f(color.R, color.G, color.B);
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(x, y);
	for (i = 0; i <= triangleAmount; i++) {
		glVertex2f(
			x + ((a + 1) * cos(i * twicePi / triangleAmount)),
			y + ((b - 1) * sin(i * twicePi / triangleAmount))
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

void Painter::FillPolygon(int n, Point points[], Color color)
{

	glColor3f(color.R, color.G, color.B);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glBegin(GL_POLYGON);

	for (int i = 0; i < n; i++)
		glVertex3f(points[i].x, points[i].y, 0.0);

	glEnd();

}

void Painter::DrawEzhik(float x, float y)
{

	int a = 100;
	int b = 115;

	Color baseColor = Color(201 / 255.f, 42 / 255.f, 114 / 255.f);
	Color glassesColor = Color(83 / 255.f, 26 / 255.f, 131 / 255.f);

	float glassRad = 30;
	float eyeRad = 20;
	float pupilRad = 5;

	float triangleSide = 100;

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
	auto points = new Point[4];
	points[0] = Point(x - a / 3 - 30, y - b / 3 - 40);
	points[1] = Point(x - a / 3 - 40, y - b / 3 - 50);
	points[2] = Point(x + a / 6 + 40, y - b / 3 - 50);
	points[3] = Point(x + a / 6 + 40, y - b / 3 - 40);

	// todo:
	FillPolygon(4, points, Color(0, 0, 0));

	// legs
	FillEllipse(x - a / 3, y + b, 15, 30, baseColor);
	FillEllipse(x + a / 3, y + b, 15, 30, baseColor);

	// arms
	FillEllipse(x - a, y + b / 2, 15, 30, baseColor);
	FillEllipse(x + a, y + b / 2, 15, 30, baseColor);

	// smile
	FillSemiCircle(x, y, 15, glassesColor);
}

