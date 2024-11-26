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

#include "Planet.h"
#include "exercise3.h"
#include "exercise4.h"

////////////////////////////////////////////////////////////
//
// system relevant global variables
//

// resolution of the of the main window (can be changed by the user)
int g_WinWidth  = 800;
int g_WinHeight = 800;

// global variable to tune the timer interval
int g_iTimerMSecs;


Planet comet;
Planet moon(&comet);
Planet earth(&moon);
Planet sun(&earth);

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
//
/////////////////////////////////////////////////////////////

#define SUN_POS CVec2f(0, 0)
#define EARTH_POS CVec2f(200, 0)
#define MOON_POS CVec2f(290, 0)
#define COMET_POS CVec2f(320, 0)


void setPlanetsCoords() {
	sun.setPosition(SUN_POS);
	earth.setPosition(EARTH_POS);
	moon.setPosition(MOON_POS);
	comet.setPosition(COMET_POS);

}

// Function to initialize our own variables
void init () 
{
	sun.setColor(Yellow);
	earth.setColor(Red);
	moon.setColor(Blue);
	comet.setColor(Cyan);

	setPlanetsCoords();

	sun.setRadius(80);
	earth.setRadius(40);
	moon.setRadius(20);
	comet.setRadius(5);

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
	float b = 70.0f / 100.0f;
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

float factor = 1.0f;
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

// display callback function for EXERCISE 3
void displayExercise3(void)
{
	affineRotateAroundOrigin(earth, 0.02f * factor);
	affineRotateAroundPoint(earth.getPosition(), moon, 0.05f * factor);
	affineRotateAroundPoint(moon.getPosition(), comet, 0.1f * factor);

	glClear (GL_COLOR_BUFFER_BIT);

	sun.draw();
	earth.draw();
	moon.draw();
	comet.draw();

	// In double buffer mode the last two lines should always be
	glFlush ();
	glutSwapBuffers (); // swap front and back buffer
}


// display callback function for EXERCISE 4
void displayExercise4(void)
{
	CMat3f m = homogenousRotateAroundOrigin(earth, 0.02f * factor);
	//rotateHomogenous2dMat(0.02f * factor);
	CMat3f em = affineInverse(trans2dMat(earth.getPosition()));
	homogenousRotateAroundPoint(em, moon);
	std::cout << moon.getPosition()[0] << "::" << moon.getPosition()[1] << std::endl;

	glClear (GL_COLOR_BUFFER_BIT);

	sun.draw();
	earth.draw();
	moon.draw();

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
		case '1':
			setPlanetsCoords();
			glutDisplayFunc (displayExercise3);
			break;
		case '2':
			setPlanetsCoords();
			glutDisplayFunc (displayExercise4);
			break;
		case '+':
			factor += 0.5f;
			break;
		case '-':
			factor -= 0.5f;
			break;
		case ' ':
			factor = 1.0f;
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
	glutCreateWindow("Computer graphics assignment 2: 2d-Rotations (WS24/25)");
	glutReshapeWindow(g_WinWidth, g_WinHeight);

	init  ();	// init my variables first
	initGL();	// init the GL (i.e. view settings, ...)

	glutTimerFunc(10, timer, 0);
	glutReshapeFunc (reshape);			// is triggered on window size changes
	glutDisplayFunc (displayExercise4);	// is triggered to redraw the viewport/display
	glutKeyboardFunc(keyboard);			// is triggered on keyboard events

	// start main loop
	glutMainLoop ();

	return 0;
}
