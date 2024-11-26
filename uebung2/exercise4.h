#pragma once

#include "Planet.h"
#include "Matrix.h"

void homogenousRotateAroundOrigin(Planet& planet, const float theta);
void homogenousRotateAroundPlanet(const Planet& toOrbit, Planet& planet, const float theta);