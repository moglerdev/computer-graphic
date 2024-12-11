#ifndef EXERCISE7_H
#define EXERCISE7_H

#include <glm/mat4x4.hpp>
#include <glm/vec4.hpp>

glm::mat4x4 rotateMatrixX(float theta);
glm::mat4x4 rotateMatrixY(float theta);
glm::mat4x4 rotateMatrixZ(float theta);
glm::mat4x4 translation(glm::vec4 t);

#endif // EXERCISE7_H