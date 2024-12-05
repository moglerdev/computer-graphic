////////////////////////////////////////////////////////////////////////////
//																	      //
// Code framework for lecture computer graphics WS 2024/25 assignment 2   //
//										                                  //
////////////////////////////////////////////////////////////////////////////

#include "Vector.h"
#include "Matrix.h"

#include <iostream>

// Include-File for GLUT-Library
#include <GL/glut.h>

#include "Cube.h"
#include "exercise6.h"
#include "bresenham.h"
#include "vector"

////////////////////////////////////////////////////////////
//
// system relevant global variables
//

// resolution of the of the main window (can be changed by the user)
int g_WinWidth  = 600;
int g_WinHeight = 600;

// global variable to tune the timer interval
int g_iTimerMSecs;

//
/////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
//
// private, global variables ... REPLACE BY YOUR OWN ONES
//
// some global state variables used to describe ...
float g_iPos;			// ... position and ...
float g_iPosIncr;		// ... position increment (used in display1)

CVec2i g_vecPos;		// same as above but in vector form ...
CVec2i g_vecPosIncr;	// (used in display2)

float g_fFocus;
std::vector<Cube>* g_cubes = nullptr;

CVec4f g_viewOrigin, g_viewDir, g_viewUp;

//
/////////////////////////////////////////////////////////////

// Function to initialize our own variables
void init () 
{
	if (g_cubes != nullptr) {
		delete g_cubes;
	}
	g_cubes = new std::vector<Cube>();
	g_cubes->push_back(Cube(CVec3f(150, 0, 10), 50, Color(1, 0, 0)));
	g_cubes->push_back(Cube(CVec3f(-150, 0, 20), 50, Color(0, 1, 0)));
	g_cubes->push_back(Cube(CVec3f(0, 150, 30), 50, Color(0, 0, 1)));

	g_fFocus = 200;

	g_viewDir = CVec4f({0, 0, -1, 0});
	g_viewOrigin = CVec4f({0, 0, 0, 1});
	g_viewUp = CVec4f({0, 1, 0, 0});

	// init timer interval
	g_iTimerMSecs = 10;

	// init variables for display1
	g_iPos     = 0;
	g_iPosIncr = 2;

	// init variables for display2
	int aiPos    [2] = {0, 0};
	int aiPosIncr[2] = {2, 2};
	g_vecPos.setData (aiPos);
	g_vecPosIncr.setData (aiPosIncr);
}

// Function to initialize the view to ortho-projection.
// Please do not change.
void initGL () 
{
	glViewport (0, 0, g_WinWidth, g_WinHeight);		// Establish viewport to cover entire window.

	glMatrixMode (GL_PROJECTION);					// Start modifying the projection matrix.
	glLoadIdentity ();								// Init projection matrix.
	glOrtho (-g_WinWidth  /2, g_WinWidth  /2,		// Map abstract coords directly to window coords.
			 -g_WinHeight /2, g_WinHeight /2, 0, 1);	
	glDrawBuffer (GL_BACK);							// Tell GL that we draw to the back buffer and swap ...
													// ... buffers when image is ready to avoid flickering	
	float b = 0;//70.0f / 100.0f;
	glClearColor(b, b, b, 1.0f);					// Tell which color to use to clear image
}

// Callback Function to change the window size.
// Please do not change.
void reshape(int w, int h)
{
	g_WinWidth  = w;
	g_WinHeight = h;
	glViewport(0, 0, w, h);							// Establish viewport to cover entire window.

	glMatrixMode(GL_PROJECTION);					// Start modifying the projection matrix.
	glLoadIdentity();								// Reset projection matrix.
	glOrtho(-w / 2, w / 2, -h / 2, h / 2, 0, 1);	// Map abstract coords directly to window coords.

	glutPostRedisplay();
}

// timer callback function
void timer (int value) 
{
	///////
	// UPDATE YOUR VARIABLES HERE ...
	//

	//
	///////

	// These variables are just for the heaving triangles
	int size2 = std::min (g_WinWidth, g_WinHeight) / 2;

	// variables for displayExercise3 ... REPLACE BY YOUR OWN ONES
	if (g_iPos<=-size2 || g_iPos>=size2) g_iPosIncr = -g_iPosIncr;
	g_iPos += g_iPosIncr;

	// variables for displayExercise4 ... REPLACE BY YOUR OWN ONES
	if (g_vecPos[1]<=-size2 || g_vecPos[1]>=size2) g_vecPosIncr = -g_vecPosIncr; 
	g_vecPos += g_vecPosIncr;

	// the last two lines should always be
	glutPostRedisplay ();
	glutTimerFunc (g_iTimerMSecs, timer, 0);	// call timer for next iteration
}

// display callback function for EXERCISE 4
void display(void)
{
	glClear (GL_COLOR_BUFFER_BIT);	// clear the color buffer

	
	for(auto& cube : *g_cubes) {
		cube.render(g_fFocus);
	}

	// In double buffer mode the last two lines should always be
	glFlush ();
	glutSwapBuffers (); // swap front and back buffer
}

void keyboard (unsigned char key, int x, int y) 
{
	switch (key) {
		case 'q':
		case 'Q':
			exit (0); // quit program
			break;
		case 'F':
			g_fFocus += 10;
			break;
		case 'f':
			g_fFocus -= 10;
			break;
		case 'X':
			break;
		case 'x':
			break;
		case 'Y':
			break;
		case 'y':
			break;
		case 'Z':
			break;
		case 'z':
			break;
		case 'A':
			break;
		case 'a':
			break;
		case 'B':
			break;
		case 'b':
			break;	
		case 'C':
			break;
		case 'c':
			break;
		case 'U':
			break;
		case 'u':
			break;
		case 'V':
			break;
		case 'v':
			break;
		case 'W':
			break;
		case 'w':
			break;
		case 'R':
		case 'r':
			init();
			break;
		default:
			// do nothing ...
			break;
	};
}

// The main
// Please do not change.
int main (int argc, char **argv) 
{
	glutInit (&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
	glutCreateWindow("Computer graphics assignment 3: 3d Projection (WS24/25)");
	glutReshapeWindow(g_WinWidth, g_WinHeight);

	init  ();	// init my variables first
	initGL();	// init the GL (i.e. view settings, ...)

	glutTimerFunc(10, timer, 0);
	glutReshapeFunc (reshape);			// is triggered on window size changes
	glutDisplayFunc (display);	// is triggered to redraw the viewport/display
	glutKeyboardFunc(keyboard);			// is triggered on keyboard events

	// start main loop
	glutMainLoop ();

	return 0;
}
