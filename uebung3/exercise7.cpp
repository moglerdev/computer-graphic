#include "exercise7.h"

CMat4f rotateMatrixX(float theta) {
	CMat4f mat;
	mat.setRow({1, 0, 0, 0}, 0);
	mat.setRow({0, cos(theta), -sin(theta), 0}, 1);
	mat.setRow({0, sin(theta), cos(theta), 0}, 2);
	mat.setRow({0, 0, 0, 1}, 3);
	return mat;
}

CMat4f rotateMatrixY(float theta) {
	CMat4f mat;
	mat.setRow({cos(theta), 0, sin(theta), 0}, 0);
	mat.setRow({0, 1, 0, 0}, 1);
	mat.setRow({-sin(theta), 0, cos(theta), 0}, 2);
	mat.setRow({0, 0, 0, 1}, 3);
	return mat;
}

CMat4f rotateMatrixZ(float theta) {
	CMat4f mat;
	mat.setRow({cos(theta), -sin(theta), 0, 0}, 0);
	mat.setRow({sin(theta), cos(theta), 0, 0}, 1);
	mat.setRow({0, 0, 1, 0}, 2);
	mat.setRow({0, 0, 0, 1}, 3);
	return mat;
}

CMat4f translation(CVec4f t) {
	CMat4f mat;
	mat.setRow({1, 0, 0, t[0]}, 0);
	mat.setRow({0, 1, 0, t[1]}, 1);
	mat.setRow({0, 0, 1, t[2]}, 2);
	mat.setRow({0, 0, 0, 1}, 3);
	return mat;
}
