#include <iostream>
#include <GLUT/glut.h>
#include "screenPt.h"

using std::cout;
using std::endl;
using std::cin;

const GLsizei WIN_POS_X = 50;
const GLsizei WIN_POS_Y = 50;
GLsizei WIN_SIZE_W = 800;
GLsizei WIN_SIZE_H = 600;
const double PI = 3.1415926;

screenPt vert, center;
GLint listId = -1;
GLuint vertNum = 6;
GLint polySize = 200;
GLdouble theta;
void init() {
	glClearColor(1.0, 1.0, 1.0, 0.0);


	listId = glGenLists(1);
	glNewList(listId, GL_COMPILE);


	glColor3f(0, 0, 0);
	center.setCoords(WIN_SIZE_W / 2, WIN_SIZE_H / 2);

	glBegin(GL_POLYGON);
	for (size_t i = 0; i < vertNum; i++)
	{
		theta = 2 * PI * i / vertNum;
		vert.setCoords(center.getX() + polySize * cos(theta), center.getY() + polySize * sin(theta));
		glVertex2i(vert.getX(), vert.getY());
	}
	glEnd();

	glEndList();
}


void displayFunc() {
	glClear(GL_COLOR_BUFFER_BIT);

	glCallList(listId);

	glFlush();

}

// 如何实现改变窗口大小时图形也随之改变（自适应）
void wndReshapeFunc(int newWidth, int newHeight) {
	glViewport(0, 0, newWidth, newHeight);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, (GLdouble)newWidth, 0, (GLdouble)newHeight);

	WIN_SIZE_W = newWidth;
	WIN_SIZE_H = newHeight;

}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(WIN_POS_X, WIN_POS_Y);
	glutInitWindowSize(WIN_SIZE_W, WIN_SIZE_H);
	glutCreateWindow("Hello World");

	init();

	glutDisplayFunc(displayFunc);
	glutReshapeFunc(wndReshapeFunc);


	glutMainLoop();

	return 0;
}