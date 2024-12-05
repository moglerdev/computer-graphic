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

    public: 
        Cube(CVec3f _center, float _size, Color _c);
        void setPos(CVec3f pos) {
            this->position = pos;
        }
        void setRotateX(float theta) {
            this->thetaX = theta;
        }
        void render(CMat4f transform, float fFocus);
};

#endif // CUBE_H
