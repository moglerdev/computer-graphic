#include "exercise5.h"

#include "Cube.h"
#include "Matrix.h"
#include "Vector.h"

Cube::Cube(CVec3f _center, float _size, Color _c) : position(_center), size(_size), color(_c) {
    this->thetaX = 0;
}

void Cube::render(CMat4f transform, float fFocus) {
    // Front face
    this->cube[0] = CVec3f(position[0] - size / 2, position[1] - size / 2, position[2] - size / 2);
    this->cube[1] = CVec3f(position[0] + size / 2, position[1] - size / 2, position[2] - size / 2);
    this->cube[2] = CVec3f(position[0] + size / 2, position[1] + size / 2, position[2] - size / 2);
    this->cube[3] = CVec3f(position[0] - size / 2, position[1] + size / 2, position[2] - size / 2);

    // Back face
    this->cube[4] = CVec3f(position[0] - size / 2, position[1] - size / 2, position[2] + size / 2);
    this->cube[5] = CVec3f(position[0] + size / 2, position[1] - size / 2, position[2] + size / 2);
    this->cube[6] = CVec3f(position[0] + size / 2, position[1] + size / 2, position[2] + size / 2);
    this->cube[7] = CVec3f(position[0] - size / 2, position[1] + size / 2, position[2] + size / 2);

    drawQuader(this->cube, fFocus, this->color);
}
