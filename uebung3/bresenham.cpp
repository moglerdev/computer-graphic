#include "bresenham.h"

#include <GL/freeglut.h>
#include "Vector.h"

void BresenhamLine(CVec2f p1, CVec2f p2, CVec4f c) 
{
	glColor4f(c[0], c[1], c[2], c[3]);
    int dx =  abs(p2[0] - p1[0]), sx = p1[0] < p2[0] ? 1 : -1;
    int dy = -abs(p2[1] - p1[1]), sy = p1[1] < p2[1] ? 1 : -1;
    int err = dx + dy, e2; /* error value e_xy */
	CVec2f p(p1);

    while (1) {
        glVertex2i(p[0], p[1]);
        if (p[0] == p2[0] && p[1] == p2[1]) break;
        e2 = 2 * err;
        if (e2 > dy) { err += dy; p[0] += sx; } /* e_xy+e_x > 0 */
        if (e2 < dx) { err += dx; p[1] += sy; } /* e_xy+e_y < 0 */
    }
}

void BresenhamCircle (CVec2f p, int r, CVec4f c)
{
	glColor4f(c[0], c[1], c[2], c[3]);

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
}
