#include "exercise6.h"
#include "exercise5.h"

/**
 * that computes the 4x4- transformation-matrix to converts view-coordinates to world-coordinates, 
 *   see Figure 2. The inverse of this matrix transforms world-coordinates to view-coordinates.
 * @param ViewOrigin a general view-origin ViewOrigin (in homogenous world-coordinates),
 * @param ViewDir a general view-direction ViewDir (in homogenous world-coordinates), and 
 * @param ViewUp a general view-up-vector ViewUp (in homogenous world- coordinates)
 */
CMat4f getTransform(CVec4f ViewOrigin, CVec4f ViewDir, CVec4f ViewUp) {
    CVec4f z = ViewDir.normalized();
    CVec4f y = ViewUp.normalized();
    CVec4f x = y.crossH(z).normalized();
    CVec4f t = ViewOrigin;

    CMat4f matTransf;
    matTransf.setRow({x[0], y[0], z[0], t[0]}, 0);
    matTransf.setRow({x[1], y[1], z[1], t[1]}, 1);
    matTransf.setRow({x[2], y[2], z[2], t[2]}, 2);
    matTransf.setRow({   0,    0,    0,    1}, 3);

    return matTransf;
}

CMat4f getInverseTransform(CVec4f ViewOrigin, CVec4f ViewDir, CVec4f ViewUp) {
    CMat4f inverse;
    CMat4f matTransf = getTransform(ViewOrigin, ViewDir, ViewUp);
    CVec3f t = {matTransf.getRow(0)[3], matTransf.getRow(1)[3], matTransf.getRow(2)[3]};
    CMat3f R;
    R.setRow(matTransf.getRow(0).getSubVector(), 0);
    R.setRow(matTransf.getRow(1).getSubVector(), 1);
    R.setRow(matTransf.getRow(2).getSubVector(), 2);
}

/**
 * that transforms the point pWorld in world coordinates via matTransf to view-coordinates and 
*  projects it onto the image plane using projectZ. 
 */
CVec4f projectZ(CMat4f matTransf, float fFocus, CVec4f pWorld) {
    CVec4f pView = matTransf * pWorld;
    CVec4f pProj = projectZ(fFocus, pView);
    return pProj;
}


void drawCuboid(CMat4f matTransf, CVec3f Cuboid[8], float fFocus, Color c) {
    CVec3f pPoint[8];
    for(int i = 0; i < 8; ++i) {
        pPoint[i] = projectZ(matTransf, fFocus, CVec4f(Cuboid[i], 1));
    }
    drawProjectedZ(pPoint, c);
}
