#include "exercise5.h"
#include "exercise6.h"

#include "Cube.h"

Cube::Cube(glm::vec3 _center, float _size, Color _c) : position(_center), size(_size), color(_c) {
    this->thetaX = 0;
    updateCuboid();
}

void Cube::updateCuboid() {
    // Front face
    this->cuboid[0] = glm::vec3(position[0] - size / 2, position[1] - size / 2, position[2] - size / 2);
    this->cuboid[1] = glm::vec3(position[0] + size / 2, position[1] - size / 2, position[2] - size / 2);
    this->cuboid[2] = glm::vec3(position[0] + size / 2, position[1] + size / 2, position[2] - size / 2);
    this->cuboid[3] = glm::vec3(position[0] - size / 2, position[1] + size / 2, position[2] - size / 2);

    // Back face
    this->cuboid[4] = glm::vec3(position[0] - size / 2, position[1] - size / 2, position[2] + size / 2);
    this->cuboid[5] = glm::vec3(position[0] + size / 2, position[1] - size / 2, position[2] + size / 2);
    this->cuboid[6] = glm::vec3(position[0] + size / 2, position[1] + size / 2, position[2] + size / 2);
    this->cuboid[7] = glm::vec3(position[0] - size / 2, position[1] + size / 2, position[2] + size / 2);
}
