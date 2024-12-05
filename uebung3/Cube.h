#ifndef CUBE_H
#define CUBE_H

#include "Vector.h"
#include "Color.h"

class Cube {
    private:
        CVec3f cube[8];
        Color color;
        CVec3f position;
        float size;
        float thetaX;
        void adjustCube();

    public: 
        Cube(CVec3f _center, float _size, Color _c);
        void rotateX(float theta);
        void setPos(CVec3f pos);
        void render(float fFocus);
};

#endif // CUBE_H
