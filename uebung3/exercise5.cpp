#include "exercise5.h"

#include "Vector.h"
#include "Matrix.h"
#include "Color.h"
#include "bresenham.h"


CVec4f projectZ(float fFocus, CVec4f pView) {
    float dx = pView[0] * (fFocus/(fFocus-pView[2]));
    float dy = pView[1] * (fFocus/(fFocus-pView[2]));

    float p[] = {dx, dy, 0, 1};
    return CVec4f(p);
}

static int edges[12][2] = {
    {0, 1}, {1, 2}, {2, 3}, {3, 0},
    {4, 5}, {5, 6}, {6, 7}, {7, 4},
    {0, 4}, {1, 5}, {2, 6}, {3, 7}
};

void drawProjectedZ(CVec3f Points[8], Color c) {
    for (int i = 0; i < 12; ++i) {
        CVec2f p1(Points[edges[i][0]][0], Points[edges[i][0]][1]);
        CVec2f p2(Points[edges[i][1]][0], Points[edges[i][1]][1]);
        BresenhamLine(p1, p2, c);
    }
}

void drawCuboid(CVec3f Cuboid[8], float fFocus, Color c) {
    CVec3f pPoint[8];
    for(int i = 0; i < 8; ++i) {
        pPoint[i] = projectZ(fFocus, CVec4f(Cuboid[i], 1));
    }
    drawProjectedZ(pPoint, c);
}
