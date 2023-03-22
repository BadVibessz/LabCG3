#include "glut.h"
#include <cmath>
#include "Painter.h"

static const int WINDOW_WIDTH = 600;
static const int WINDOW_HEIGTH = 600;
const float M_PI = 3.14159265358979323846f;

int g_windowWidth = WINDOW_WIDTH;
int g_windowHeight = WINDOW_HEIGTH;

using namespace std;


void OnResizeWindow(int width, int height)
{
	//float wDiffCoeff = (float)width / g_windowWidth;
	//float hDiffCoeff = (float)height / g_windowHeight;


	//g_windowWidth = width;
	//g_windowHeight = height;

	//PixelCoordConverter::width = g_windowWidth;
	//PixelCoordConverter::height = g_windowHeight;

	//glViewport(0, 0, width, height);
	//glMatrixMode(GL_PROJECTION);
	//glLoadIdentity();

	//float aspectRatio = (float)width / height;
	////gluPerspective(45, aspectRatio, 0,100);
	////glOrtho(-aspectRatio, (float)width - aspectRatio, (float)height - aspectRatio, 0, -1, 1);

	////glOrtho(-aspectRatio, aspectRatio, -1000, 1000, -1.0, 1.0);

	//glOrtho(0, width, height, 0, -1, 1);


	///*if (width > height)
	//	glOrtho(-aspectRatio, aspectRatio, 0, 0, -1.0, 1.0);
	//else
	//	glOrtho(0,0, -aspectRatio, aspectRatio, -1.0, 1.0);*/

	//glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();

	PixelCoordConverter::width = g_windowWidth;
	PixelCoordConverter::height = g_windowHeight;

	float oldRatio = (float)g_windowWidth / (float)g_windowHeight;
	float newRatio = (float)width / (float)height;

	float wDiffCoeff = (float)width / (float)g_windowWidth;
	float hDiffCoeff = (float)height / (float)g_windowHeight;

	if (newRatio > oldRatio)
		wDiffCoeff = hDiffCoeff;
	else hDiffCoeff = wDiffCoeff;

	float xOffset = (width - g_windowWidth * wDiffCoeff) / 2;
	float yOffset = (height - g_windowHeight * hDiffCoeff) / 2;

	glViewport(xOffset, yOffset, g_windowWidth * wDiffCoeff, g_windowHeight * hDiffCoeff);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(0, g_windowWidth / oldRatio, g_windowHeight / oldRatio, 0, -1, 1.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}


void OnDrawSceneFunctionWindow()
{

	Painter::DrawAxes(g_windowWidth, g_windowHeight, Color(1, 1, 1));

	auto function = [](float x) { return 2 * x * x - 3 * x - 8; };
	Painter::DrawFunction(function, -2, 3,
		g_windowWidth, g_windowHeight, Color(218 / 255.f, 165 / 255.f, 32 / 255.f));

	glFlush();

}



// ezhik position
float x = g_windowWidth / 2;
float y = g_windowHeight / 2;

// ezhik rectangle
float top = y - 175;
float bottom = y + 115;
float left = x - 100;
float right = x + 100;

float dx = 0, dy = 0;

bool isDragging = false;

void RefreshEzhikRectangle()
{
	top = y - 175;
	bottom = y + 115;
	left = x - 100;
	right = x + 100;
}


void OnDrawSceneEzhikWindow()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	Painter::DrawEzhik(x, y);
	glutSwapBuffers();
	RefreshEzhikRectangle();
}

void OnMouseMove(int mouseX, int mouseY)
{
	if (isDragging)
	{
		x = mouseX - dx;
		y = mouseY - dy;

		glutPostRedisplay();
	}
}

void OnMouseClick(int button, int state, int mouseX, int mouseY)
{

	if (state == GLUT_DOWN)
	{
		switch (button)
		{
		case GLUT_LEFT_BUTTON:

			if (mouseX > left && mouseX < right && mouseY > top && mouseY < bottom)
			{
				isDragging = true;

				dx = mouseX - x;
				dy = mouseY - y;
			}
		}
	}
	else
		isDragging = false;

}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_MULTISAMPLE);

	// window one
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGTH);
	glutCreateWindow("Function");
	glutReshapeFunc(&OnResizeWindow);
	glutDisplayFunc(&OnDrawSceneFunctionWindow);


	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_MULTISAMPLE);

	// window two
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGTH);
	glutCreateWindow("Ezhik");
	glutReshapeFunc(&OnResizeWindow);
	glutDisplayFunc(&OnDrawSceneEzhikWindow);
	glutMouseFunc(&OnMouseClick);
	glutMotionFunc(&OnMouseMove);

	glutMainLoop();

	return 0;
}

