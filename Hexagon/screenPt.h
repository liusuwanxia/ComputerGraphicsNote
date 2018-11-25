#ifndef SCREEN_PT
#define SCREEN_PT

#include <GLUT/glut.h>

class screenPt {
private:
	GLint x, y;
public:
	screenPt() {
		x = y = 0;
	}

	void setCoords(GLint xCoord, GLint yCoord) {
		x = xCoord;
		y = yCoord;
	}

	GLint getX() const {
		return x;
	}

	GLint getY() const {
		return y;
	}
};

#endif // !SCREEN_PT
