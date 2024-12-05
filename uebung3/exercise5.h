#ifndef EXERCISE5_H
#define EXERCISE5_H

#include "Vector.h"
#include "Matrix.h"
#include "Color.h"

CVec4f projectZ(float fFocus, CVec4f pView);
void drawProjectedZ(CVec3f Points[8], Color c);

void drawCuboid(CVec3f Cuboid[8], float fFocus, Color c);

#endif // EXERCISE5_H