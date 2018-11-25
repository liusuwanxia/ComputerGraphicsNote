#include "PropertyTest.h"
#include "globalDefine.h"

void blendTest() {
	glColor3f(0.5, 0.0, 0.0);
	glBegin(GL_TRIANGLES);
	glVertex2i(10, 10);
	glVertex2i(WIN_SIZE_W - 10, 10);
	glVertex2i(10, WIN_SIZE_H - 10);
	glEnd();

	// ��Ҫ��ʹ�õ�ʹ�ÿ���, ���õ�ʱ��ر�
	// ��ΪClear Color BufferʱҲ���õ�, ���رտ��ܵ�����ֵ�����
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

// ������glBegin�ڲ������ⲿ���� glColor3f, ������Ч��������ȫ�ֵ�
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

	// �����˳������˶���εĳ���
	// Ĭ������£����㰴��ʱ��˳�����е���Ϊǰ���棬����Ϊ������
	// ��˲����������ã���
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
	// ͨ��ʹ�ò�ͬ��Polygon Mode�������λ���������ʵ�ִ��в�ͬ��ɫ�����ߵĶ����
	glColor3f(0.0, 0.0, 1.0);
	glPolygonMode(GL_FRONT, GL_FILL);
	glCallList(listNo);
	glColor3f(1.0, 1.0, 1.0);
	glPolygonMode(GL_FRONT, GL_LINE);
	glCallList(listNo);
	
	
}

