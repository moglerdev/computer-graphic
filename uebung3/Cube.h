#ifndef CUBE_H
#define CUBE_H

#include <array>
#include "Vector.h"
#include "Color.h"
#include "Matrix.h"

class Cube {
    private:
        std::array<CVec3f, 8> cuboid;
        Color color;
        CVec3f position;
        float size;
        float thetaX;

        void updateCuboid();

    public: 
        Cube(CVec3f _center, float _size, Color _c);
        void setPos(CVec3f pos) {
            this->position = pos;
            updateCuboid();
        }
        void setRotateX(float theta) {
            this->thetaX = theta;
            updateCuboid();
        }

        Color getColor() const {
            return this->color;
        }
        
        const std::array<CVec3f, 8> getCuboids() const {
            return this->cuboid;
        }
};

#endif // CUBE_H
