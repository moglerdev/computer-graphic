////////////////////////////////////////////////////////////////////////////
//																	      //
// Code framework for lecture computer graphics WS 2024/25 assignment 4   //
//										                                  //
////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////
// 
// INCLUDES
// 
/////////////////////////////////////////////////////////////

// include-file for text in-/output
#include <iostream>
using namespace std;

// include-file for GLUT-Library
#include <GL/glut.h>

// my own include-files
#include <glm/glm.hpp>
#include "Color.h"
#include "cg_math.h"
#include "Sphere.h"

#include "exercise8.h"
#include "exercise9.h"

/////////////////////////////////////////////////////////////
// 
// GLOBAL VARIABLES
// 
/////////////////////////////////////////////////////////////

// resolution of texture 
// !!!ATTENTION!!! not every resolution works!
#define TEX_RES_X 400
#define TEX_RES_Y 400
// Number of pixel of texture
#define TEX_RES TEX_RES_X*TEX_RES_Y
// length of texture's axis is asymmetric: -TexRes#/2 to TexRes#/2-1

// global texture buffer
char g_Buffer[3*TEX_RES];
// texture ID 
GLuint g_TexID = 0;

// resolution of main window (can be changed by user)
int g_WinWidth  = 400;
int g_WinHeight = 400;

// increments for interaction
double illum_inc     = 0.05;		// increment for illumination values
double color_inc     = 0.05;		// increment for color        values
double light_inc     = 0.1;			// increment for angles in spherical angles for light source position
double shininess_inc = 5.0;

// scene parameters
Sphere sphere(glm::vec3(0, 0, 100), 50);

// light source and camera parameters
int A = -1; // eye-point
Color  backColor = Color(0.8,0.8,0.8);

Light light(1000.0, 1.5*PI, 0);

// forward declarations
void clearTexture (                 const Color& c = backColor);
void setPixel     (const glm::ivec2& p, const Color& c = backColor);


/////////////////////////////////////////////////////////////
// 
// PLEASE-DO-NOT-CHANGE FUNCTIONS
// 
///////////////////////////////////////////////////////////// 

// Functions to set up the texture.
// Please do not change!
void manageTexture () 
{
	glEnable (GL_TEXTURE_2D);

	if (g_TexID==0) glGenTextures(1, &g_TexID);

	glBindTexture  (GL_TEXTURE_2D , g_TexID);
	glTexEnvf      (GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE  , GL_REPLACE);
	glTexParameterf(GL_TEXTURE_2D , GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D , GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D , GL_TEXTURE_WRAP_S    , GL_CLAMP  );
	glTexParameterf(GL_TEXTURE_2D , GL_TEXTURE_WRAP_T    , GL_CLAMP  );

	glTexImage2D (GL_TEXTURE_2D, 0, GL_RGB, TEX_RES_X, TEX_RES_Y, 0, GL_RGB, GL_UNSIGNED_BYTE, g_Buffer);	
	glBindTexture(GL_TEXTURE_2D, 0);

	glDisable    (GL_TEXTURE_2D);
}

// Functions to map the texture.
// Please do not change!
void mapTexture() 
{
	glBindTexture (GL_TEXTURE_2D, g_TexID);	
	glEnable      (GL_TEXTURE_2D);

	glBegin (GL_QUADS);
	glColor3d   (1.0, 0.0, 0.0);
	glTexCoord2d(0.0, 0.0);
	glVertex2d  (-g_WinWidth/2.0, -g_WinHeight/2.0);
	glTexCoord2d(1.0, 0.0);
	glVertex2d  ( g_WinWidth/2.0, -g_WinHeight/2.0);
	glTexCoord2d(1.0, 1.0);
	glVertex2d  ( g_WinWidth/2.0,  g_WinHeight/2.0);
	glTexCoord2d(0.0, 1.0);
	glVertex2d  (-g_WinWidth/2.0,  g_WinHeight/2.0);
	glEnd ();

	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable    (GL_TEXTURE_2D);
}

// Callback function to adjust the window size.
// Please do not change!
void reshape(int w, int h) 
{
	g_WinWidth = w;
	g_WinHeight = h;

	glViewport(0, 0, w, h);						// Establish viewport to cover entire window.

	glMatrixMode(GL_PROJECTION);				// Start modifying the projection matrix.
	glLoadIdentity();							// Reset projection matrix.
	glOrtho(-w/2, w/2, -h/2, h/2, 0, 1);		// Map abstract coords directly to window coords.

	glutPostRedisplay ();
}

// Function plots a pixel p with color c to the texture. 
// Please do not change it, but use it!
void setPixel(const glm::ivec2& p, const Color& c) 
{
	if (p[0] < 0 || p[1] < 0 || p[0] > TEX_RES_X || p[1] > TEX_RES_Y) {
		cerr << "Illegal pixel co-ordinates (" << p[0] << ", " << p[1] << ")\n" << flush;
		return;
	}
	
	g_Buffer[3 * TO_LINEAR(p[0], p[1])    ] = char(255.0 * c.r);
	g_Buffer[3 * TO_LINEAR(p[0], p[1]) + 1] = char(255.0 * c.g);
	g_Buffer[3 * TO_LINEAR(p[0], p[1]) + 2] = char(255.0 * c.b);
}

// Callback function controlling the repaint of the display.
// Please do not change!
void display() 
{
	manageTexture  ();	
	glClear        (GL_COLOR_BUFFER_BIT);	
	mapTexture     ();
	glFlush        ();
	glutSwapBuffers();
}

// Callback function initializing the repaint of the display.
// Please do not change!
void init() 
{
	affLight = SphericalToAffine(sphLight);
	rayCast();
}

std::string vec3ToString(glm::vec3 vec) {
	std::string x;
	x += "(";
	for (unsigned j = 0; j < 3; j++) x += to_string(vec[j]) + ",";
	x += to_string(vec[2]) + ")";
	return x;
}

// Callback function to handle keyboard input.
// Please do not change!
void keyboard(unsigned char c, int x, int y) 
{
	glm::vec3 inc(illum_inc,illum_inc,illum_inc);
	switch (c) {

		/////////////////////////////////
		// Light source
		/////////////////////////////////
		case 'x': sphLight[1] = crop(PI, 2 * PI, sphLight[1] - light_inc); break;
		case 'X': sphLight[1] = crop(PI, 2 * PI, sphLight[1] + light_inc); break;
		case 'y': sphLight[2] = crop( 0,     PI, sphLight[2] - light_inc); break;
		case 'Y': sphLight[2] = crop( 0,     PI, sphLight[2] + light_inc); break;
		case 'z': sphLight[0] -= 50; break;
		case 'Z': sphLight[0] += 50; break;

		/////////////////////////////////
		// Color of sphere
		/////////////////////////////////
		case 'r': diffuseColor.r = crop(diffuseColor.r - color_inc); break;
		case 'R': diffuseColor.r = crop(diffuseColor.r + color_inc); break;
		case 'g': diffuseColor.g = crop(diffuseColor.g - color_inc); break;
		case 'G': diffuseColor.g = crop(diffuseColor.g + color_inc); break;
		case 'b': diffuseColor.b = crop(diffuseColor.b - color_inc); break;
		case 'B': diffuseColor.b = crop(diffuseColor.b + color_inc); break;

		/////////////////////////////////
		// Color of light source
		/////////////////////////////////
		case 'c': specularColor.r = crop(specularColor.r - color_inc); break;
		case 'C': specularColor.r = crop(specularColor.r + color_inc); break;
		case 'e': specularColor.g = crop(specularColor.g - color_inc); break;
		case 'E': specularColor.g = crop(specularColor.g + color_inc); break;
		case 'f': specularColor.b = crop(specularColor.b - color_inc); break;
		case 'F': specularColor.b = crop(specularColor.b + color_inc); break;

		/////////////////////////////////
		// Color of environment
		/////////////////////////////////
		case 'u': ambientColor.r = crop(ambientColor.r - color_inc); break;
		case 'U': ambientColor.r = crop(ambientColor.r + color_inc); break;
		case 'v': ambientColor.g = crop(ambientColor.g - color_inc); break;
		case 'V': ambientColor.g = crop(ambientColor.g + color_inc); break;
		case 'w': ambientColor.b = crop(ambientColor.b - color_inc); break;
		case 'W': ambientColor.b = crop(ambientColor.b + color_inc); break;

		/////////////////////////////////
		// Shininess
		/////////////////////////////////
		case 's': shininess -= min(shininess_inc, shininess / 2); shininess = max(0.0, shininess);  break;
		case 'S': shininess += min(shininess_inc, shininess); break;

		/////////////////////////////////
		// Illumination level
		/////////////////////////////////
		case '1': diffuseIllumination  = crop(diffuseIllumination  - inc); break;		// diffuse  illumination
		case '2': diffuseIllumination  = crop(diffuseIllumination  + inc); break;		// diffuse  illumination
		case '3': specularIllumination = crop(specularIllumination - inc); break;		// specular illumination
		case '4': specularIllumination = crop(specularIllumination + inc); break;		// specular illumination
		case '5': ambientIllumination  = crop(ambientIllumination  - inc); break;		// ambient  illumination
		case '6': ambientIllumination =  crop(ambientIllumination  + inc); break;		// ambient  illumination
		
		/////////////////////////////////
		// Radius
		/////////////////////////////////
		case 'd': sphere.setRadius(sphere.getRadius()-1); break;
		case 'D': sphere.setRadius(sphere.getRadius()+1); break;

		/////////////////////////////////
		// Material properties of sphere
		/////////////////////////////////
		case 'M': material = (material+1)%3; break;

		/////////////////////////////////
		// Quit
		/////////////////////////////////
		case 'q':
		case 'Q': exit (0); break;

		/////////////////////////////////
		// Help menue
		/////////////////////////////////
		default:	
			cout << "Use 'x', 'X', 'y', and 'Y'           to move   the light source"						<< endl; 
			cout << "Use 'r', 'R', 'g', 'G', 'b', and 'B' to change the diffuse  color"						<< endl; 
			cout << "Use 'c', 'C', 'e', 'E', 'f', and 'F' to change the specular color"						<< endl;
			cout << "Use 'u', 'U', 'v', 'V', 'w', and 'W' to change the ambient  color"						<< endl; 
			cout << "Use '1' and '2'                      to change the diffuse  illumination level"		<< endl; 
			cout << "Use '3' and '4'                      to change the specular illumination level"		<< endl;
			cout << "Use '5' and '6'                      to change the ambient  illumination level"		<< endl; 
			cout << "Use 's' and 'S'                      to change the shininess"							<< endl; 
			cout << "Use 'd' and 'D'                      to change the radius"								<< endl; 
			cout << "Use 'M'                              to change the material (normal/Messing/Bronze)"	<< endl; 
			cout << "Use 'q' or 'Q'                       to quit"											<< endl; 
			break;
	}
	cout << "Diffuse  color and illumination level: "	<< diffuseColor  << ", " << vec3ToString(diffuseIllumination)		<< endl;
	cout << "Specular color and illumination level: "	<< specularColor << ", " << vec3ToString(specularIllumination)	<< endl;
	cout << "Ambient  color and illumination level: "	<< ambientColor  << ", " << vec3ToString(ambientIllumination)		<< endl;
	cout << "Shininess :"								<< shininess										<< endl;
	cout << "Material: "								<< material											<< endl;

	affLight=SphericalToAffine(sphLight);
	rayCast();	
	glutPostRedisplay();
}

// This is the main function, triggering the GLUT-Main-Loop
// Please do not change!
int main (int argc, char **argv) {
	
	init();

	glutInit (&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
	glutInitWindowSize (g_WinWidth, g_WinHeight);

	glutCreateWindow ("Assignment 4: Phong Illumination (WS24/25)");
	
	glutKeyboardFunc(keyboard);		// handles keyboard input
	glutReshapeFunc (reshape);		// handles changes of window size
	glutDisplayFunc (display);		// handles repainting of the display
	
	glutMainLoop ();				// transfering the control to GLUT

	glDeleteTextures (1, &g_TexID);	// deletes the defined textures

	return 0;
}
