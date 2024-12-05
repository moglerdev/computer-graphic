#include "bresenham.h"

#include <GL/freeglut.h>
#include "Vector.h"

void BresenhamLine(CVec2f p1, CVec2f p2, Color c) 
{
    glBegin(GL_POINTS);
    glColor3f(c.r, c.g, c.b); // Set the line color

    // Calculate differences and step directions
    int dx = abs((int)p2[0] - (int)p1[0]); 
    int sx = (p1[0] < p2[0]) ? 1 : -1; 
    int dy = -abs((int)p2[1] - (int)p1[1]); 
    int sy = (p1[1] < p2[1]) ? 1 : -1; 

    int err = dx + dy; // Error term
    int e2; // Double the error term

    CVec2i pxI((int)p1[0], (int)p1[1]); // Start point as integers
    CVec2i p2I((int)p2[0], (int)p2[1]); // End point as integers

    while (true) {
        glVertex2i(pxI[0], pxI[1]); // Plot the point
        if (pxI[0] == p2I[0] && pxI[1] == p2I[1]) 
            break; // Terminate if we reach the end point
        
        e2 = 2 * err; 
        if (e2 >= dy) { 
            err += dy; // Adjust error term
            pxI[0] += sx; // Move in the x-direction
        }
        if (e2 <= dx) { 
            err += dx; // Adjust error term
            pxI[1] += sy; // Move in the y-direction
        }
    }

    glEnd();
}

void BresenhamCircle (CVec2f p, int r, Color c)
{
	glBegin(GL_POINTS);
	
	glColor3f(c.r, c.g, c.b);

	glVertex2i(p[0] + r, p[1]);
	glVertex2i(p[0]    , p[1] + r);
	glVertex2i(p[0] - r, p[1]);
	glVertex2i(p[0]    , p[1] - r);

	int x, y, d, dSE, dE;
	x = 0; y = r;
	d = 5 - 4 * r;

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

		glVertex2i(p[0] + x, p[1] + y);
		glVertex2i(p[0] + x, p[1] - y);
		glVertex2i(p[0] - x, p[1] + y);
		glVertex2i(p[0] - x, p[1] - y);

		glVertex2i(p[0] + y, p[1] + x);
		glVertex2i(p[0] + y, p[1] - x);
		glVertex2i(p[0] - y, p[1] + x);
		glVertex2i(p[0] - y, p[1] - x);
	}

	glEnd();
}
