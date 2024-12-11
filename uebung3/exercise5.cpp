#include "exercise5.h"

#include <glm/vec2.hpp>

#include "Color.h"
#include "bresenham.h"


glm::vec4 projectZ(float fFocus, glm::vec4 pView) {
    float dx = pView[0] * (fFocus/(fFocus-pView[2]));
    float dy = pView[1] * (fFocus/(fFocus-pView[2]));

    return glm::vec4({dx, dy, 0, 1});
}

static int edges[12][2] = {
    {0, 1}, {1, 2}, {2, 3}, {3, 0},
    {4, 5}, {5, 6}, {6, 7}, {7, 4},
    {0, 4}, {1, 5}, {2, 6}, {3, 7}
};

void drawProjectedZ(glm::vec3 Points[8], Color c) {
    for (int i = 0; i < 12; ++i) {
        glm::vec2 p1(Points[edges[i][0]][0], Points[edges[i][0]][1]);
        glm::vec2 p2(Points[edges[i][1]][0], Points[edges[i][1]][1]);
        BresenhamLine(p1, p2, c);
    }
}

void drawCuboid(glm::vec3 Cuboid[8], float fFocus, Color c) {
    glm::vec3 pPoint[8];
    for(int i = 0; i < 8; ++i) {
        pPoint[i] = projectZ(fFocus, glm::vec4(Cuboid[i], 1));
    }
    drawProjectedZ(pPoint, c);
}
