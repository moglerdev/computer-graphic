#include "exercise6.h"
#include "exercise5.h"

/**
 * that computes the 4x4- transformation-matrix to converts view-coordinates to world-coordinates, 
 *   see Figure 2. The inverse of this matrix transforms world-coordinates to view-coordinates.
 * @param ViewOrigin a general view-origin ViewOrigin (in homogenous world-coordinates),
 * @param ViewDir a general view-direction ViewDir (in homogenous world-coordinates), and 
 * @param ViewUp a general view-up-vector ViewUp (in homogenous world- coordinates)
 */
glm::mat4 getTransform(glm::vec4 ViewOrigin, glm::vec4 ViewDir, glm::vec4 ViewUp) {
    glm::vec3 z = -glm::vec3(ViewDir);
    glm::vec3 y = glm::vec3(ViewUp);
    glm::vec3 x = glm::normalize(glm::cross(y, z));
    y = glm::normalize(y);
    z = glm::normalize(z);

    glm::mat4 matTransf(1.0f); // Identity matrix
    matTransf[0] = glm::vec4(x, 0.0f);
    matTransf[1] = glm::vec4(y, 0.0f);
    matTransf[2] = glm::vec4(z, 0.0f);
    matTransf[3] = ViewOrigin;

    return matTransf;
}

glm::mat4 getInverseTransform(glm::vec4 ViewOrigin, glm::vec4 ViewDir, glm::vec4 ViewUp) {
    return glm::inverse(getTransform(ViewOrigin, ViewDir, ViewUp));
}

glm::vec4 projectZ(glm::mat4 matTransf, float fFocus, glm::vec4 pWorld) {
    glm::vec4 pView = matTransf * pWorld;
    return projectZ(fFocus, pView);
}

void drawCuboid(glm::mat4 matTransf, glm::vec3 Cuboid[8], float fFocus, Color c) {
    glm::vec3 pPoint[8];
    for (int i = 0; i < 8; ++i) {
        glm::vec4 pWorld = glm::vec4(Cuboid[i], 1.0f);
        glm::vec4 pProjected = projectZ(matTransf, fFocus, pWorld);
        pPoint[i] = glm::vec3(pProjected);
    }
    drawProjectedZ(pPoint, c);
}


// Check if a point is inside the frustum
bool isPointInFrustum(const glm::vec4& point, const glm::mat4& matProjView) {
    glm::vec4 clipSpace = matProjView * point;

    // Perform homogeneous clipping: -w <= x, y, z <= w
    return (clipSpace.x >= -clipSpace.w && clipSpace.x <= clipSpace.w &&
            clipSpace.y >= -clipSpace.w && clipSpace.y <= clipSpace.w &&
            clipSpace.z >= -clipSpace.w && clipSpace.z <= clipSpace.w);
}

// Check if a cuboid is inside the frustum
bool isCuboidInFrustum(const glm::vec3 cuboid[8], const glm::mat4& matProjView) {
    for (int i = 0; i < 8; ++i) {
        glm::vec4 worldPoint = glm::vec4(cuboid[i], 1.0f);
        if (isPointInFrustum(worldPoint, matProjView)) {
            return true; // At least one point is inside
        }
    }
    return false; // No points inside, cull the cuboid
}
