#ifndef EXERCISE5_H
#define EXERCISE5_H

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include "Color.h"

glm::vec4 projectZ(float fFocus, glm::vec4 pView);
void drawProjectedZ(glm::vec3 Points[8], Color c);

void drawCuboid(glm::vec3 Cuboid[8], float fFocus, Color c);

#endif // EXERCISE5_H
