#pragma once

#include "Planet.h"

void affineRotateAroundOrigin(Planet& planet, float theta);
void affineRotateAroundPoint(const CVec2f& point, Planet& planet, float theta);
