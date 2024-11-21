////////////////////////////////////////////////////////////////////////////
//																	      //
// Code framework for lecture computer graphics WS 2024/25 assignment 2   //
//										                                  //
// A class for circular objects, e.g. planets                             //
//										                                  //
// (c) Georg Umlauf						                                  //
//										                                  //
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
//																	      //
// Code framework for lecture computer graphics WS 2024/25 assignment 2   //
//										                                  //
// A class for circular objects, e.g. planets                             //
//										                                  //
// (c) Georg Umlauf						                                  //
//										                                  //
////////////////////////////////////////////////////////////////////////////

#include "Planet.h"

#include <GL/glut.h>

//
// Implement HERE your Bresenham algorithm for circles 
//
void Planet::draw() const
{
	glBegin(GL_POINTS);
	glColor3d(color.r, color.g, color.b);
	// ...

	// implement BresenhamCircle here and use
	// glVertex2i (x, y);
	// to draw a pixel at (x,y)

	glVertex2i(this->position[0] + this->radius, this->position[1]);
	glVertex2i(this->position[0]    , this->position[1] + this->radius);
	glVertex2i(this->position[0] - this->radius, this->position[1]);
	glVertex2i(this->position[0]    , this->position[1] - this->radius);

	int x, y, d, dSE, dE;
	x = 0; y = this->radius;
	d = 5 - 4 * this->radius;

	while(y > x) {
		if (d >= 0) {
			dSE = 4 * (2 * (x - y) + 5);
			d += dSE; 
			++x;
			--y;
		} else {
			dE = 4 * (2 * x + 3);
			d += dE;
			++x;
		}

		glVertex2i(this->position[0] + x, this->position[1] + y);
		glVertex2i(this->position[0] + x, this->position[1] - y);
		glVertex2i(this->position[0] - x, this->position[1] + y);
		glVertex2i(this->position[0] - x, this->position[1] - y);

		glVertex2i(this->position[0] + y, this->position[1] + x);
		glVertex2i(this->position[0] + y, this->position[1] - x);
		glVertex2i(this->position[0] - y, this->position[1] + x);
		glVertex2i(this->position[0] - y, this->position[1] - x);
	}

	// ...
	glEnd();
}
