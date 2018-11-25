#include <iostream>
#include <GLUT/glut.h>
#include "globalDefine.h"
#include "OpenGLAlgorithm.h"

using std::cout;
using std::endl;
using std::cin;



void init() {
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0, WIN_SIZE_W, 0, WIN_SIZE_H);

	
}




void displayFunc() {
	glClear(GL_COLOR_BUFFER_BIT);

	//blendTest();
	//colorTest();
	//lineStippleTest();
	//polygonModeTest();	
	for (size_t i = 0; i < WIN_SIZE_W; i++)
	{
		setPixel(i, 100);
	}

	glFlush();

}


int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(WIN_POS_X, WIN_POS_Y);
	glutInitWindowSize(WIN_SIZE_W, WIN_SIZE_H);
	glutCreateWindow(title);

	init();

	glutDisplayFunc(displayFunc);

	glutMainLoop();

	return 0;
}