#include "OpenGLAlgorithm.h"
#include <GLUT/glut.h>

inline int round(const float val) {
	return int(val + 0.5);
}

inline int fabs(int val) {
	return val > 0 ? val : -val;
}

void setPixel(int x, int y)
{
	glRasterPos2i(x, y);
	GLubyte color[3] = { 255,255,255 };
	glDrawPixels(1, 1, GL_RGB, GL_UNSIGNED_BYTE, color);
}

void DAA(int x0, int xEnd, int y0, int yEnd) {
	int dx = fabs(xEnd - x0);
	int dy = fabs(yEnd - y0);
	int steps = dx > dy ? dx : dy;
	float xInc = (float)dx / steps;
	float yInc = (float)dy / steps;

	float x = x0, y = y0;

	setPixel(round(x), round(y));
	for (int i = 0; i < steps; i++)
	{
		x += xInc;
		y += yInc;
		setPixel((int)x, (int)y);
	}
}


void Bresenham(int x0, int xEnd, int y0, int yEnd)
{
	int x, y;

	// 首先确保x方向一定是递增的
	if (x0 > xEnd) {
		x = xEnd;
		y = yEnd;
		xEnd = x0;
		yEnd = y0;
	}
	else {
		x = x0;
		y = y0;
	}

	int dx = xEnd - x, dy = yEnd - y, ady = fabs(dy);
	double px = 2 * ady - dx;
	double py = 2 * dx - ady;
	double twoDy = 2 * ady, twoDyMinesDx = 2 * (ady - dx);
	double twoDx = 2 * dx, twoDxMinesDy = 2 * (dx - ady);

	setPixel(x, y);

	// -1 < m < 0 以及  0 < m < 1 两种情况
	if (ady < dx) {
		while (x < xEnd) {
			x++;
			if (px < 0)
				px += twoDy;
			else {
				if (dy > 0)
					y++;
				else
					y--;
				px += twoDyMinesDx;
			}
			setPixel(x, y);
		}
	}
	// 对于 m > 1 以及 m < -1 的情况
	else {
		if (dy > 0) {
			while (y < yEnd) {
				y++;
				if (py < 0) {
					py += twoDx;
				}
				else {
					x++;
					py += twoDxMinesDy;
				}
				setPixel(x, y);
			}
		}
		else {
			while (y > yEnd) {
				if (dy > 0)
				{
					y++;
				}
				else {
					y--;
				}
				if (py < 0) {
					py += twoDx;
				}
				else {
					x++;
					py += twoDxMinesDy;
				}
				setPixel(x, y);
			}
		}
	}
}
