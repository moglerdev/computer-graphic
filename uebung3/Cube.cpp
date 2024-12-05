#include "exercise5.h"
#include "exercise6.h"

#include "Cube.h"
#include "Matrix.h"
#include "Vector.h"

Cube::Cube(CVec3f _center, float _size, Color _c) : position(_center), size(_size), color(_c) {
    this->thetaX = 0;
    updateCuboid();
}

void Cube::updateCuboid() {
    // Front face
    this->cuboid[0] = CVec3f(position[0] - size / 2, position[1] - size / 2, position[2] - size / 2);
    this->cuboid[1] = CVec3f(position[0] + size / 2, position[1] - size / 2, position[2] - size / 2);
    this->cuboid[2] = CVec3f(position[0] + size / 2, position[1] + size / 2, position[2] - size / 2);
    this->cuboid[3] = CVec3f(position[0] - size / 2, position[1] + size / 2, position[2] - size / 2);

    // Back face
    this->cuboid[4] = CVec3f(position[0] - size / 2, position[1] - size / 2, position[2] + size / 2);
    this->cuboid[5] = CVec3f(position[0] + size / 2, position[1] - size / 2, position[2] + size / 2);
    this->cuboid[6] = CVec3f(position[0] + size / 2, position[1] + size / 2, position[2] + size / 2);
    this->cuboid[7] = CVec3f(position[0] - size / 2, position[1] + size / 2, position[2] + size / 2);
}
