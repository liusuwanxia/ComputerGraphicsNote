#include "OpenGLAlgorithm.h"
#include <GLUT/glut.h>

inline int round(const float val) {
	return int(val + 0.5);
}

inline int fabs(int val) {
	return val > 0 ? val : -val;
}

void setPixel(GLint x, GLint y)
{
	glRasterPos2i(x, y);
	GLubyte color[3] = { 255,255,255 };
	glDrawPixels(1, 1, GL_RGB, GL_UNSIGNED_BYTE, color);

	/*glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();*/

}

void DAA(GLint x0, GLint xEnd, GLint y0, GLint yEnd) {
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


void Bresenham(GLint x0, GLint xEnd, GLint y0, GLint yEnd, GLint width, void (*drawfunc)(GLint x, GLint y, GLboolean horizontalDriven, GLint width))
{
	int x, y;

	// ����ȷ��x����һ���ǵ�����
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

	// �����ʱ��Ϊˮƽ����
	drawfunc(x, y, true, width);

	// ������� x����������ٶȴ��� y����
	// -1 < m < 0 �Լ�  0 < m < 1 �������
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
			drawfunc(x, y, true, width);
		}
	}
	// ������� y����������ٶȴ��� x����
	// ���� m > 1 �Լ� m < -1 �����
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
				drawfunc(x, y, false, width);
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
				drawfunc(x, y, false, width);
			}
		}
	}


}

void setPixelWrap(GLint x, GLint y, GLboolean driven, GLint width) {
	setPixel(x, y);
}
 void setPixelWithWidth(GLint x, GLint y, GLboolean driven, GLint width) {
	bool sign = true;
	for (int i = 0; i < width; i++)
	{
		GLint temp_x = x;
		GLint temp_y = y;
		if (driven)
		{
			temp_y = sign ? temp_y + (i + 1) / 2 : temp_y - (i + 1) / 2;
		}
		else {
			temp_x = sign ? temp_x + (i + 1) / 2 : temp_x - (i + 1) / 2;
		}
		setPixel(temp_x, temp_y);

		sign = !sign;
	}
}

void drawSimpleLine(GLint x0, GLint xEnd, GLint y0, GLint yEnd) {
	Bresenham(x0, xEnd, y0, yEnd, 1, setPixelWrap);
}

void drawWideLine(GLint x0, GLint xEnd, GLint y0, GLint yEnd, GLint width) {
	Bresenham(x0, xEnd, y0, yEnd, width, setPixelWithWidth);
}

class screenPt {
private:
	GLint x, y;

public:
	screenPt() {
		x = y = 0;
	}
	void setCoords(GLint xCoordValue, GLint yCoordValue) {
		x = xCoordValue;
		y = yCoordValue;
	}

	GLint getx() const {
		return x;
	}

	GLint gety() const {
		return y;
	}

	void incrementx() {
		x++;
	}

	void decrementy() {
		y--;
	}
};

void circleMidpoGLint(GLint xc, GLint yc, GLint radius)
{
	screenPt circPt;

	GLint p = 1 - radius;

	circPt.setCoords(0, radius);

	void circlePlotPoints(GLint, GLint, screenPt);
	circlePlotPoints(xc, yc, circPt);

	while (circPt.getx() < circPt.gety())
	{
		circPt.incrementx();
		if (p < 0)
		{
			p += 2 * circPt.getx() + 1;
		}
		else {
			circPt.decrementy();
			p += 2 * (circPt.getx() - circPt.gety()) + 1;
		}
		circlePlotPoints(xc, yc, circPt);
	}
}

void circlePlotPoints(GLint xc, GLint yc, screenPt circPt) {
	setPixel(xc + circPt.getx(), yc + circPt.gety());
	setPixel(xc - circPt.getx(), yc + circPt.gety());
	setPixel(xc + circPt.getx(), yc - circPt.gety());
	setPixel(xc - circPt.getx(), yc - circPt.gety());
	setPixel(xc + circPt.gety(), yc + circPt.getx());
	setPixel(xc - circPt.gety(), yc + circPt.getx());
	setPixel(xc + circPt.gety(), yc - circPt.getx());
	setPixel(xc - circPt.gety(), yc - circPt.getx());
}
