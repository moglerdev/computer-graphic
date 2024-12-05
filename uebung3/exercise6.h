#ifndef EXERCISE6_H
#define EXERCISE6_H

#include "Matrix.h"
#include "Vector.h"
#include "Color.h"

/**
 * that computes the 4x4- transformation-matrix to converts view-coordinates to world-coordinates, 
 *   see Figure 2. The inverse of this matrix transforms world-coordinates to view-coordinates. 
 */
CMat4f getTransform(CVec4f ViewOrigin, CVec4f ViewDir, CVec4f ViewUp);

CMat4f getInverseTransform(CVec4f ViewOrigin, CVec4f ViewDir, CVec4f ViewUp);

/**
 * that transforms the point pWorld in world coordinates via matTransf to view-coordinates and 
*  projects it onto the image plane using projectZ. 
 */
CVec4f projectZallg(CMat4f matTransf, float fFocus, CVec4f pWorld);


void drawCuboid(CMat4f matTransf, CVec3f Cuboid[8], float fFocus, Color c);
#endif // EXERCISE6_H