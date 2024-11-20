﻿//////////////////////////////////////////////////////////////////////////
//																	    //
// Code framework for lecture computer graphics WS 2024/25 exercise 1   //
//										                                //
//////////////////////////////////////////////////////////////////////////


// Include-Ffile for io
#include <iostream>
using namespace std;

#include "Point.h"
#include "Color.h"

// Include-File for GLUT-Library
#include <GL/glut.h>


//////////////////////////////////////////////////////////////////////////
//
// some initializations
//
//


// resolution of the complete texture
// !!!ATTENTION!!! some resolutions for the texture do not work -> POT2 problem
#define TEX_RES_X 60
#define TEX_RES_Y 60
// number of pixels of the texture
#define TEX_RES TEX_RES_X*TEX_RES_Y
// length of axes for the texture (axes are asymmetric from -TexRes#/2 to TesRes#/2-1)
#define TEX_HALF_X TEX_RES_X/2
#define TEX_HALF_Y TEX_RES_Y/2
// converting indices from (x,y) coordinats to a linear array used in the texture buffer
#define TO_LINEAR(x, y) (((x)) + TEX_RES_X*((y)))

// global memory for texture
char g_Buffer[3*TEX_RES];
// texture ID name
GLuint g_TexID = 0;

// resolution of the of the main window (can be changed by the user)
int g_WinWidth = 800;
int g_WinHeight = 800;

// Function to organize the texture.
void manageTexture () 
{
	glEnable        (GL_TEXTURE_2D);
	if (g_TexID==0) glGenTextures (1, &g_TexID);
	glBindTexture   (GL_TEXTURE_2D, g_TexID);
	glTexEnvf       (GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glTexParameterf (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameterf (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexImage2D    (GL_TEXTURE_2D, 0, GL_RGB, TEX_RES_X, TEX_RES_Y, 0, GL_RGB, GL_UNSIGNED_BYTE, g_Buffer);	
	glBindTexture   (GL_TEXTURE_2D, 0);
	glDisable       (GL_TEXTURE_2D);
}

// Callback Function to change the window size.
void reshape(int w, int h) 
{
	g_WinWidth = w;
	g_WinHeight = h;
	glViewport(0, 0, w, h);					// Establish viewport to cover entire window.

	glMatrixMode(GL_PROJECTION);			// Start modifying the projection matrix.
	glLoadIdentity();						// Reset project matrix.
	glOrtho(-w/2, w/2, -h/2, h/2, 0, 1);	// Map abstract coords directly to window coords.

	glutPostRedisplay ();
}


/////////////////////////////////////////////////////////////////////////////////////////
//
// Here starts the part relevant for the exercise.
//

//
// Function clears the viewport/display with the given color
// - Usage z.B.: clearImage (Color (1,1,1)) clears tht viewport with white
// - If no parameter is given, white is used as default.
//
void clearDisplay(Color c=Color()) 
{
	for (int i=0; i<TEX_RES; i++) {
		g_Buffer[3 * i    ] = int(255.0 * c.r);
		g_Buffer[3 * i + 1] = int(255.0 * c.g);
		g_Buffer[3 * i + 2] = int(255.0 * c.b);
	}
}

//
// Functions plot a point at the given coordinates p in color c
// - Usage z.B.: setPoint (Point(10, 5), Color (1,0,0)) plots red point at (10, 5)
// - It no color is given, black is used as default
//	- USE THIS FUNCTION TO PLOT POINT IN YOUR BESENHAM
//
void setPoint (Point p, Color c=Color(0,0,0)) 
{
	int x = p.x + TEX_HALF_X;
	int y = p.y + TEX_HALF_Y;
	if (x < 0 || y < 0 || x >= TEX_RES_X || y >= TEX_RES_Y) {
		cerr << "Illegal point co-ordinates (" << p.x << ", " << p.y << ")\n" << flush;
		return;
	}

	g_Buffer[3 * TO_LINEAR(x, y)    ] = int(255.0 * c.r);
	g_Buffer[3 * TO_LINEAR(x, y) + 1] = int(255.0 * c.g);
	g_Buffer[3 * TO_LINEAR(x, y) + 2] = int(255.0 * c.b);
}

//
// Assignment 1 Exercise 1
//
// Implement this function to draw a line from p1 to p2 in color c using Besenham's algorithm.
// - Use setPoint to plot individual points/pixels.
// 
void BresenhamLine(Point p1, Point p2, Color c) 
{
    int dx =  abs(p2.x - p1.x), sx = p1.x < p2.x ? 1 : -1;
    int dy = -abs(p2.y - p1.y), sy = p1.y < p2.y ? 1 : -1;
    int err = dx + dy, e2; /* error value e_xy */
	Point p(p1.x, p1.y);

    while (1) {
        setPoint(p, c);
        if (p.x == p2.x && p.y == p2.y) break;
        e2 = 2 * err;
        if (e2 > dy) { err += dy; p.x += sx; } /* e_xy+e_x > 0 */
        if (e2 < dx) { err += dx; p.y += sy; } /* e_xy+e_y < 0 */
    }
}


//
// Assignment 1 Exercise 2
//
// Implement this function to draw a circle with radius r around mid-point p in color c using Besenham's algorithm.
// - Use setPoint to plot individual points/pixels.
// - Also plot the mid-point.
// 
void BresenhamCircle (Point p, int r, Color c)
{
	setPoint(Point(p.x + r, p.y));
	setPoint(Point(p.x    , p.y + r));
	setPoint(Point(p.x - r, p.y));
	setPoint(Point(p.x    , p.y - r));

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

		setPoint(Point(p.x + x, p.y + y));
		setPoint(Point(p.x + x, p.y - y));
		setPoint(Point(p.x - x, p.y + y));
		setPoint(Point(p.x - x, p.y - y));

		setPoint(Point(p.x + y, p.y + x));
		setPoint(Point(p.x + y, p.y - x));
		setPoint(Point(p.x - y, p.y + x));
		setPoint(Point(p.x - y, p.y - x));
	}
}

//
// This (callback) function triggers a redraw of then viewport/display. 
// - Please consider only the part marked in the comments.
//
void display (void) 
{
	Color background(0.5,0.5,0.5);	// grey background
    clearDisplay(background);		// clears the old display

	//////////////////////////////////////////////////////////////////
	//
	// Here the functions to draw lines and circles are invoked. 
	// - Define here the relevant parameters.
	// - Call   here the relevant functions.
	// - Try    here different parameter settings, i.e. start point, end point, mid-point, radius.
	//

    Point p1  (-10,  20);				// first point of the line, aka start point
	Point p2  ( 25, -10);				// last  point of the line, aka end   point
    Point p3  (0,  -20);				// first point of the line, aka start point
	Point p4  (0, 10);				// last  point of the line, aka end   point
	Color cRed(1,0,0);					// color       of the line
	BresenhamLine  (p1, p2, cRed);		// plot the line
	BresenhamLine  (p3, p4, cRed);		// plot the line

	int r = 17;							// radius    of the circle
	Point p(-3, -5);					// mid-point of the circle
	Color cBlue(0,0,1);					// color     of the circle
	BresenhamCircle (p, r, cBlue);		// plot the circle

	//
    // Please, do not change below this point!
	//
	//////////////////////////////////////////////////////////////////

	manageTexture ();

	glClear      (GL_COLOR_BUFFER_BIT);
	glBindTexture(GL_TEXTURE_2D, g_TexID);	
	glEnable     (GL_TEXTURE_2D);

	glBegin     (GL_QUADS);
	glColor3f   (1, 0, 0);
	glTexCoord2f(0, 0); glVertex2f  (-g_WinWidth/2.0f, -g_WinHeight/2.0f);
	glTexCoord2f(1, 0);	glVertex2f  ( g_WinWidth/2.0f, -g_WinHeight/2.0f);
	glTexCoord2f(1, 1);	glVertex2f  ( g_WinWidth/2.0f,  g_WinHeight/2.0f);
	glTexCoord2f(0, 1);	glVertex2f  (-g_WinWidth/2.0f,  g_WinHeight/2.0f);
	glEnd       ();

	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable    (GL_TEXTURE_2D);

	glFlush ();
}

// The main
int main (int argc, char **argv) {

	glutInit (&argc, argv);
	glutInitWindowSize (g_WinWidth, g_WinHeight);
    glutCreateWindow ("Computer graphics exercise 1: Bresenham (WS24/25)");

    glutReshapeFunc (reshape);	// is triggered on window size changes
    glutDisplayFunc (display);	// is triggered to redraw the viewport/display

	glutMainLoop ();

    glDeleteTextures (1, &g_TexID); // deletes the texture

	return 0;
}
