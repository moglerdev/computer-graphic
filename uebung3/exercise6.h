#ifndef EXERCISE6_H
#define EXERCISE6_H

#include <glm/mat4x4.hpp>
#include <glm/vec4.hpp>
#include <glm/vec3.hpp>
#include "Color.h"

/**
 * that computes the 4x4- transformation-matrix to converts view-coordinates to world-coordinates, 
 *   see Figure 2. The inverse of this matrix transforms world-coordinates to view-coordinates. 
 */
glm::mat4 getTransform(glm::vec4 ViewOrigin, glm::vec4 ViewDir, glm::vec4 ViewUp);

glm::mat4 getInverseTransform(glm::vec4 ViewOrigin, glm::vec4 ViewDir, glm::vec4 ViewUp);

/**
 * that transforms the point pWorld in world coordinates via matTransf to view-coordinates and 
*  projects it onto the image plane using projectZ. 
 */
glm::vec4 projectZ(glm::mat4 matTransf, float fFocus, glm::vec4 pWorld);

// Check if a point is inside the frustum
bool isPointInFrustum(const glm::vec4& point, const glm::mat4& matProjView);

// Check if a cuboid is inside the frustum
bool isCuboidInFrustum(const glm::vec3 cuboid[8], const glm::mat4& matProjView);

void drawCuboid(glm::mat4 matTransf, glm::vec3 Cuboid[8], float fFocus, Color c);
#endif // EXERCISE6_H