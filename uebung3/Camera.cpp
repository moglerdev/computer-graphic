#include "Camera.h"

#include <glm/mat4x4.hpp>

#include "exercise7.h"
#include "exercise6.h"
#include "exercise5.h"

#define ROTATE_SPEED 0.1
#define MOVE_SPEED 10

void Camera::render() {
    glm::mat4 matTransf = getInverseTransform(viewOrigin, viewDir, viewUp);

    for (auto cube : this->cubes) {
        auto cuboid = cube->getCuboids();

        // Draw the cuboid if it's visible
        drawCuboid(matTransf, cuboid.data(), fFocus, cube->getColor());
    }
}

void Camera::setPose(const glm::mat4& mat) {
    viewDir = glm::normalize(mat * viewDir);
    viewUp = glm::normalize(mat * viewUp);
}

void Camera::rotateWorldX(float theta) {
	glm::mat4 mat = rotateMatrixX(theta);
    viewOrigin = mat * viewOrigin;
	setPose(mat);
}
void Camera::rotateWorldY(float theta) {
	glm::mat4 mat = rotateMatrixY(theta);
    viewOrigin = mat * viewOrigin;
	setPose(mat);
}
void Camera::rotateWorldZ(float theta) {
	glm::mat4 mat = rotateMatrixZ(theta);
    viewOrigin = mat * viewOrigin;
	setPose(mat);
}

void Camera::rotateLocalX(float theta) {
    // Rotate around the local X-axis (viewRight)
	glm::mat4 mat = translation(viewOrigin) * rotateMatrixX(theta) * translation(-viewOrigin);
    viewOrigin = mat * viewOrigin;
	setPose(mat);
}

void Camera::rotateLocalY(float theta) {
    // Rotate around the local Y-axis (viewUp)
	glm::mat4 mat = translation(viewOrigin) * rotateMatrixY(theta) * translation(-viewOrigin);
    viewOrigin = mat * viewOrigin;
	setPose(mat);
}

void Camera::rotateLocalZ(float theta) {
    // Rotate around the local Z-axis (viewDir)
	glm::mat4 mat = translation(viewOrigin) * rotateMatrixZ(theta) * translation(-viewOrigin);
    viewOrigin = mat * viewOrigin;
	setPose(mat);
}

void Camera::addX(float x) {
    this->viewOrigin[0] += x;
}
void Camera::addY(float y) {
    this->viewOrigin[1] += y;
}
void Camera::addZ(float z) {
    this->viewOrigin[2] += z;
}

// adjust the focus of the camera
#define KEY_ADD_FOCUS 'F'
#define KEY_SUB_FOCUS 'f'

// Rotate around world x-axis
#define KEY_ROTATE_WORLD_POS_X 'X'
#define KEY_ROTATE_WORLD_NEG_X 'x'
// Rotate around local x-axis
#define KEY_ROTATE_LOCAL_POS_X 'A'
#define KEY_ROTATE_LOCAL_NEG_X 'a'

// Rotate around world y-axis
#define KEY_ROTATE_WORLD_POS_Y 'Y'
#define KEY_ROTATE_WORLD_NEG_Y 'y'
// Rotate around local y-axis
#define KEY_ROTATE_LOCAL_POS_Y 'B'
#define KEY_ROTATE_LOCAL_NEG_Y 'b'

// Rotate around world z-axis
#define KEY_ROTATE_WORLD_POS_Z 'Z'
#define KEY_ROTATE_WORLD_NEG_Z 'z'
// Rotate around local z-axis
#define KEY_ROTATE_LOCAL_POS_Z 'C'
#define KEY_ROTATE_LOCAL_NEG_Z 'c'

// Move the camera in the x direction
#define KEY_ADD_X '4'
#define KEY_SUB_X '6'
// Move the camera in the y direction
#define KEY_ADD_Y '2'
#define KEY_SUB_Y '8'
// Move the camera in the z direction
#define KEY_ADD_Z '1'
#define KEY_SUB_Z '3'


void Camera::handleKey(std::map<unsigned char, bool> keyStates) {
    // Handle key presses for various camera controls
    if (keyStates[KEY_ADD_FOCUS]) {
        this->addFocus(10);
    }
    if (keyStates[KEY_SUB_FOCUS]) {
        this->addFocus(-10);
    }

    if (keyStates[KEY_ROTATE_WORLD_POS_X]) {
        // Rotate around world x-axis
        this->rotateWorldX(ROTATE_SPEED);
    }
    if (keyStates[KEY_ROTATE_WORLD_NEG_X]) {
        // Rotate around world x-axis
        this->rotateWorldX(-ROTATE_SPEED);
    }

    if (keyStates[KEY_ROTATE_WORLD_POS_Y]) {
        // Rotate around world y-axis
        this->rotateWorldY(ROTATE_SPEED);
    }
    if (keyStates[KEY_ROTATE_WORLD_NEG_Y]) {
        // Rotate around world y-axis
        this->rotateWorldY(-ROTATE_SPEED);
    }

    if (keyStates[KEY_ROTATE_WORLD_POS_Z]) {
        // Rotate around world z-axis
        this->rotateWorldZ(ROTATE_SPEED);
    }
    if (keyStates[KEY_ROTATE_WORLD_NEG_Z]) {
        // Rotate around world z-axis
        this->rotateWorldZ(-ROTATE_SPEED);
    }

    if (keyStates[KEY_ROTATE_LOCAL_POS_X]) {
        // Rotate around camera x-axis
        this->rotateLocalX(ROTATE_SPEED);
    }
    if (keyStates[KEY_ROTATE_LOCAL_NEG_X]) {
        // Rotate around camera x-axis
        this->rotateLocalX(-ROTATE_SPEED);
    }

    if (keyStates[KEY_ROTATE_LOCAL_POS_Y]) {
        // Rotate around camera y-axis
        this->rotateLocalY(ROTATE_SPEED);
    }
    if (keyStates[KEY_ROTATE_LOCAL_NEG_Y]) {
        // Rotate around camera y-axis
        this->rotateLocalY(-ROTATE_SPEED);
    }

    if (keyStates[KEY_ROTATE_LOCAL_POS_Z]) {
        // Rotate around camera z-axis
        this->rotateLocalZ(ROTATE_SPEED);
    }
    if (keyStates[KEY_ROTATE_LOCAL_NEG_Z]) {
        // Rotate around camera z-axis
        this->rotateLocalZ(-ROTATE_SPEED);
    }

    if (keyStates[KEY_ADD_X]) {
        this->addX(MOVE_SPEED);
    }
    if (keyStates[KEY_SUB_X]) {
        this->addX(-MOVE_SPEED);
    }

    if (keyStates[KEY_ADD_Y]) {
        this->addY(MOVE_SPEED);
    }
    if (keyStates[KEY_SUB_Y]) {
        this->addY(-MOVE_SPEED);
    }

    if (keyStates[KEY_ADD_Z]) {
        this->addZ(MOVE_SPEED);
    }
    if (keyStates[KEY_SUB_Z]) {
        this->addZ(-MOVE_SPEED);
    }
}
