#include "glut.h"
#include <cmath>
#include "Painter.h"


static const int WINDOW_WIDTH = 600;
static const int WINDOW_HEIGTH = 400;
const char WINDOW_TITLE[] = "glut";
const float M_PI = 3.14159265358979323846f;

int g_windowWidth = WINDOW_WIDTH;
int g_windowHeight = WINDOW_HEIGTH;

using namespace std;


void OnResizeWindow(int width, int height)
{
	g_windowWidth = width;
	g_windowHeight = height;

	PixelCoordConverter::width = g_windowWidth;
	PixelCoordConverter::height = g_windowHeight;

	/*
	«адаем положение и размеры видового порта (порта просмотра) в буфере кадра
	¬ывод примитивов не будет осуществл€тьс€ за его пределы
	*/
	glViewport(0, 0, width, height);

	// ƒелаем текущей матрицей OpenGL матрицу проецировани€
	glMatrixMode(GL_PROJECTION);

	// «агружаем в нее единичную матрицу
	glLoadIdentity();

	/*
	» умножаем ее на матрицу ортографического проецировани€ такую,
	что левому верхнему углу просмотра будет соответствовать
	точка (0, 0), правому нижнему - (width, height),
	а сцена будет включать в себ€ объект, расположенные по глубине в диапазоне
	от -1 (сзади) до +1 (спереди)
	*/
	glOrtho(0, width, height, 0, -1, 1);

	// ƒелаем текущей матрицей матрицу моделировани€-вида
	glMatrixMode(GL_MODELVIEW);
}


void OnDrawSceneFunctionWindow()
{

	Painter::DrawAxes(g_windowWidth, g_windowHeight, Color(1, 1, 1));

	auto function = [](float x) { return 2 * x * x - 3 * x - 8; };
	Painter::DrawFunction(function, -2, 3,
		g_windowWidth, g_windowHeight, Color(218 / 255.f, 165 / 255.f, 32 / 255.f));
	
	glFlush();

}

void OnDrawSceneEzhikWindow()
{
	Painter::DrawEzhik(g_windowWidth / 2, g_windowHeight / 2);
	glFlush();
}


int main(int argc, char* argv[])
{
	glutInit(&argc, argv);

	//glutInitDisplayMode(GLUT_RGB);

	//glutSetOption(GLUT_MULTISAMPLE, 8);
	glutInitDisplayMode(GLUT_RGB | GLUT_MULTISAMPLE);


	// window one
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGTH);
	glutCreateWindow("Function");
	glutReshapeFunc(&OnResizeWindow);
	glutDisplayFunc(&OnDrawSceneFunctionWindow);

	// window two
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGTH);
	glutCreateWindow("Ezhik");
	glutReshapeFunc(&OnResizeWindow);
	glutDisplayFunc(&OnDrawSceneEzhikWindow);

	glutMainLoop();

	return 0;
}

