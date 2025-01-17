/////////////////////////////////////////////////////////////
// 
// Framework for computer graphics assignment 4
// 
// Some useful mathematical functions
// 
// (c) Georg Umlauf, 2022
// 
/////////////////////////////////////////////////////////////

#pragma once

#include <glm/glm.hpp>
#include "Color.h"

// Conversion of indices of (x,y) coordinates to a linear array
#define TO_LINEAR(x, y) (((x)) + TEX_RES_X*((y)))

const double PI = 3.1415926535;

// crop x to interval [l,u]
double crop(double x, double l = 0.0, double u = 1.0);

// crop all componentens of x to interval [l,u]
glm::vec3 crop(const glm::vec3& x, double l = 0.0, double u = 1.0);

// crop all componentens of x to interval [l,u]
Color crop(const Color& x, double l = 0.0, double u = 1.0);

// spherical to affine coordinates
// (x) PI <= XZ <= 2Pi (X)
// (y) 0  <= YZ <=  PI (Y)
glm::vec3 SphericalToAffine(const glm::vec3& sphericalCoordinates);
