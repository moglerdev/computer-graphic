#include "exercise3.h"
#include <GL/glut.h>

CMat2f rotate2dMat(const float theta) {
	CMat2f m;
	m.setRow(CVec2f(cos(theta), -sin(theta)), 0);
	m.setRow(CVec2f(sin(theta), cos(theta)), 1);
	return m;
}

void affineRotateAroundOrigin(Planet& planet, float theta) {
	CVec2f p = rotate2dMat(theta) * planet.getPosition();
	planet.setPosition(p);
}

void affineRotateAroundPoint(const CVec2f& point, Planet& planet, float theta) {
   // Step 1: Translate the planet's position relative to the center (point)
    CVec2f translatedPosition = planet.getPosition() - point;

    // Step 2: Rotate the translated position
    CVec2f rotatedPosition = rotate2dMat(theta) * translatedPosition;

    // Step 3: Translate back by adding the point to the rotated position
    planet.setPosition(rotatedPosition + point);
}
