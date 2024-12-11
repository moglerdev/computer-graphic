#pragma once
#include <glm/vec2.hpp>
#include "Color.h"

void BresenhamLine(glm::vec2 p1, glm::vec2 p2, Color c);

void BresenhamCircle (glm::vec2 p, int r, Color c);
