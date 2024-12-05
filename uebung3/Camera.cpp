#include "Camera.h"

#include "Matrix.h"
#include "exercise7.h"
#include "exercise6.h"
#include "exercise5.h"

#define ROTATE_SPEED 0.1
#define MOVE_SPEED 10

void Camera::render() {
    CMat4f matTransf = getTransform(viewOrigin, viewDir, viewUp);
    for(auto cube : this->cubes) {
		auto cuboid = cube->getCuboids();
		drawCuboid(matTransf, cuboid.data(), fFocus, cube->getColor());
    }
}

void Camera::rotateWorldX(float theta) {
    setPose(rotateMatrixX(theta));
}
void Camera::rotateWorldY(float theta) {
    setPose(rotateMatrixY(theta));
}
void Camera::rotateWorldZ(float theta) {
    setPose(rotateMatrixZ(theta));
}

void Camera::rotateLocalX(float theta) {
    // Rotate around the local X-axis (viewRight)
	CMat4f mat = translation(viewOrigin) * rotateMatrixX(theta) * translation(-viewOrigin);
	setPose(mat);
}

void Camera::rotateLocalY(float theta) {
    // Rotate around the local Y-axis (viewUp)
	
	CMat4f mat = translation(viewOrigin) * rotateMatrixY(theta) * translation(-viewOrigin);
	setPose(mat);
}

void Camera::rotateLocalZ(float theta) {
    // Rotate around the local Z-axis (viewDir)
	
	CMat4f mat = translation(viewOrigin) * rotateMatrixZ(theta) * translation(-viewOrigin);
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
// Rotate around world y-axis
#define KEY_ROTATE_WORLD_POS_Y 'Y'
#define KEY_ROTATE_WORLD_NEG_Y 'y'
// Rotate around world z-axis
#define KEY_ROTATE_WORLD_POS_Z 'Z'
#define KEY_ROTATE_WORLD_NEG_Z 'z'

// Rotate around local x-axis
#define KEY_ROTATE_LOCAL_POS_X 'A'
#define KEY_ROTATE_LOCAL_NEG_X 'a'
// Rotate around local y-axis
#define KEY_ROTATE_LOCAL_POS_Y 'B'
#define KEY_ROTATE_LOCAL_NEG_Y 'b'
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

void Camera::handleKey(const unsigned char key) {
    switch (key)
    {
		case KEY_ADD_FOCUS:
			this->addFocus(10);
			break;
		case KEY_SUB_FOCUS:
			this->addFocus(-10);
			break;
		case KEY_ROTATE_WORLD_POS_X:
			// Rotate around world x-axis
			this->rotateWorldX(ROTATE_SPEED);
			break;
		case KEY_ROTATE_WORLD_NEG_X:
			// Rotate around world x-axis
			this->rotateWorldX(-ROTATE_SPEED);
			break;
		case KEY_ROTATE_WORLD_POS_Y:
			// Rotate around world y-axis
			this->rotateWorldY(ROTATE_SPEED);
			break;
		case KEY_ROTATE_WORLD_NEG_Y:
			// Rotate around world y-axis
			this->rotateWorldY(-ROTATE_SPEED);
			break;
		case KEY_ROTATE_WORLD_POS_Z:
			// Rotate around world y-axis
			this->rotateWorldZ(ROTATE_SPEED);
			break;
		case KEY_ROTATE_WORLD_NEG_Z:
			// Rotate around world y-axis
			this->rotateWorldZ(-ROTATE_SPEED);
			break;
		case KEY_ROTATE_LOCAL_POS_X:
			// Rotate around camera x-axis
			this->rotateLocalX(ROTATE_SPEED);
			break;
		case KEY_ROTATE_LOCAL_NEG_X:
			// Rotate around camera x-axis
			this->rotateLocalX(-ROTATE_SPEED);
			break;
		case KEY_ROTATE_LOCAL_POS_Y:
			// Rotate around camera y-axis
			this->rotateLocalY(ROTATE_SPEED);
			break;
		case KEY_ROTATE_LOCAL_NEG_Y:
			// Rotate around camera y-axis
			this->rotateLocalY(-ROTATE_SPEED);
			break;	
		case KEY_ROTATE_LOCAL_POS_Z:
			// Rotate around camera z-axis
			this->rotateLocalZ(ROTATE_SPEED);
			break;
		case KEY_ROTATE_LOCAL_NEG_Z:
			// Rotate around camera z-axis
			this->rotateLocalZ(-ROTATE_SPEED);
			break;
		case KEY_ADD_X:
			this->addX(MOVE_SPEED);
			break;
		case KEY_SUB_X:
			this->addX(-MOVE_SPEED);
			break;
		case KEY_ADD_Y:
			this->addY(MOVE_SPEED);
			break;
		case KEY_SUB_Y:
			this->addY(-MOVE_SPEED);
			break;
		case KEY_ADD_Z:
			this->addZ(MOVE_SPEED);
			break;
		case KEY_SUB_Z:
			this->addZ(-MOVE_SPEED);
			break;
        default:
            break;
    }
}