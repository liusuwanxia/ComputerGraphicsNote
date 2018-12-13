#ifndef OPENGL_ALGORITHM
#define OPENGL_ALGORITHM

#include <GLUT/glut.h>
void setPixel(GLint x, GLint y);
void DAA(GLint x0, GLint xEnd, GLint y0, GLint yEnd);
void drawSimpleLine(GLint x0, GLint xEnd, GLint y0, GLint yEnd);
void drawWideLine(GLint x0, GLint xEnd, GLint y0, GLint yEnd, GLint width);
void circleMidpoGLint(GLint xc, GLint yc, GLint radius);

#endif // !OPENGL_ALGORITHM
