#include "OpenGLAlgorithm.h"
#include <GLUT/glut.h>

void setPixel(int x, int y)
{
	glRasterPos2i(x, y);
	GLubyte color[3] = { 255,255,255 };
	glDrawPixels(1, 1, GL_RGB, GL_UNSIGNED_BYTE, color);
}
