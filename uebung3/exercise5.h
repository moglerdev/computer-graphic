#ifndef EXERCISE5_H
#define EXERCISE5_H

#include "Vector.h"
#include "Color.h"

CVec4f projectZ(float fFocus, CVec4f pView);
void drawProjektedZ(CVec3f Points[8], Color c);
void drawQuader(CVec3f Cuboid[8], float fFocus, Color c);

#endif // EXERCISE5_H