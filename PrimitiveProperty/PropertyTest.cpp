#include "PropertyTest.h"
#include "globalDefine.h"

void blendTest() {
	glColor3f(0.5, 0.0, 0.0);
	glBegin(GL_TRIANGLES);
	glVertex2i(10, 10);
	glVertex2i(WIN_SIZE_W - 10, 10);
	glVertex2i(10, WIN_SIZE_H - 10);
	glEnd();

	// 需要在使用的使用开启, 不用的时候关闭
	// 因为Clear Color Buffer时也会用到, 不关闭可能导致奇怪的现象
	glEnable(GL_BLEND);
	glBlendFunc(GL_ONE, GL_ONE);

	glColor3f(0, 0.5, 0);
	glBegin(GL_TRIANGLES);
	glVertex2i(10, 10);
	glVertex2i(WIN_SIZE_W - 10, 10);
	glVertex2i(WIN_SIZE_W - 10, WIN_SIZE_H - 10);
	glEnd();

	glDisable(GL_BLEND);
}

// 无论在glBegin内部还是外部调用 glColor3f, 产生的效果都会是全局的
void colorTest() {
	glBegin(GL_TRIANGLES);
	glColor3f(0.5, 0.0, 0.0);
	glVertex2i(10, 10);
	glVertex2i(WIN_SIZE_W - 10, 10);
	glVertex2i(10, WIN_SIZE_H - 10);
	glEnd();

	glBegin(GL_TRIANGLES);
	glVertex2i(10, 10);
	glVertex2i(WIN_SIZE_W - 10, 10);
	glVertex2i(WIN_SIZE_W - 10, WIN_SIZE_H - 10);
	glEnd();

	glDisable(GL_BLEND);
}

void lineStippleTest()
{
	Pt2D points[5] = {
		{10, 10},
	{200, 200},
	{50, 10},
	{300, 200},
	{100, 10}
	};

	glEnable(GL_LINE_STIPPLE);
	glLineStipple(1, 0x1C47);
	glLineWidth(4.0);
	glBegin(GL_LINE_STRIP);
	
	for (GLsizei i = 0; i < 5; i++)
	{
		glVertex2d(points[i].x, points[i].y);
	}
	
	glEnd();

	glDisable(GL_LINE_STIPPLE);
}

GLuint listDrawQuad() {
	GLuint listNo = glGenLists(1);

	// 顶点的顺序决定了多边形的朝向
	// 默认情况下，顶点按逆时针顺序排列的面为前向面，否则为背向面
	// 因此不能随意设置！！
	Pt2D points[4] = {
		{20, 20},
		{120, 20}, 
		{120, 120},
		{20, 120},
	};

	glNewList(listNo, GL_COMPILE);

	glBegin(GL_POLYGON);

	for (size_t i = 0; i < 4; i++)
	{
		glVertex2i(points[i].x, points[i].y);
	}

	glEnd();
	
	glEndList();

	return listNo;
}

void polygonModeTest()
{
	GLuint listNo = listDrawQuad();
	// 通过使用不同的Polygon Mode调用两次绘制例程来实现带有不同颜色轮廓线的多边形
	glColor3f(0.0, 0.0, 1.0);
	glPolygonMode(GL_FRONT, GL_FILL);
	glCallList(listNo);
	glColor3f(1.0, 1.0, 1.0);
	glPolygonMode(GL_FRONT, GL_LINE);
	glCallList(listNo);
	
	
}

