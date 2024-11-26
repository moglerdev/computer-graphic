#pragma once

#include "Planet.h"
#include "Matrix.h"

CMat3f rotateHomogenous2dMat(const float theta);
CMat3f trans2dMat(const CVec2f& position);
CMat3f homogenousRotateAroundOrigin(Planet& planet, float theta);
void homogenousRotateAroundPoint(const CMat3f& pose, Planet& planet);
