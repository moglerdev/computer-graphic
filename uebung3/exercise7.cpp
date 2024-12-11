#include "exercise7.h"

glm::mat4 rotateMatrixX(float theta) {
    glm::mat4 mat(1.0f); // Identity matrix
    mat[1][1] = cos(theta);
    mat[1][2] = -sin(theta);
    mat[2][1] = sin(theta);
    mat[2][2] = cos(theta);
    return mat;
}

glm::mat4 rotateMatrixY(float theta) {
    glm::mat4 mat(1.0f); // Identity matrix
    mat[0][0] = cos(theta);
    mat[0][2] = sin(theta);
    mat[2][0] = -sin(theta);
    mat[2][2] = cos(theta);
    return mat;
}

glm::mat4 rotateMatrixZ(float theta) {
    glm::mat4 mat(1.0f); // Identity matrix
    mat[0][0] = cos(theta);
    mat[0][1] = -sin(theta);
    mat[1][0] = sin(theta);
    mat[1][1] = cos(theta);
    return mat;
}

glm::mat4 translation(glm::vec4 t) {
    glm::mat4 mat(1.0f); // Identity matrix
    mat[3][0] = t.x;
    mat[3][1] = t.y;
    mat[3][2] = t.z;
    return mat;
}
