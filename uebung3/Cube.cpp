#include "exercise5.h"

#include "Cube.h"
#include "Matrix.h"
#include "Vector.h"

Cube::Cube(CVec3f _center, float _size, Color _c) : position(_center), size(_size), color(_c) {
    this->thetaX = 0;
    this->adjustCube();
}

void Cube::adjustCube() {
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
}

void Cube::setPos(CVec3f pos) {
    this->position = pos;
    this->rotateX(0);
    this->adjustCube();
}

void Cube::rotateX(float theta) {
    this->thetaX += theta;
    float x1[] = {1, 0, 0, 0};
    float x2[] = {0, cos(theta), -sin(theta), 0};
    float x3[] = {0, sin(theta), cos(theta), 0};
    float x4[] = {0, 0, 0, 1};

    CMat4f mRotation;
    mRotation(0, 0) = x1[0];
    mRotation(0, 1) = x1[1];
    mRotation(0, 2) = x1[2];
    mRotation(0, 3) = x1[3];

    for(int i = 0; i < 8; ++i) {
        this->cube[i] = mRotation * CVec4f(this->cube[i], 1);
    }
}

void Cube::render(float fFocus) {
    drawQuader(this->cube, fFocus, this->color);
}
