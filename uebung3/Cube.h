#ifndef CUBE_H
#define CUBE_H

#include <array>
#include <glm/vec3.hpp>
#include "Color.h"

class Cube {
    private:
        std::array<glm::vec3, 8> cuboid;
        Color color;
        glm::vec3 position;
        float size;
        float thetaX;

        void updateCuboid();

    public: 
        Cube(glm::vec3 _center, float _size, Color _c);
        void setPos(glm::vec3 pos) {
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
        
        const std::array<glm::vec3, 8> getCuboids() const {
            return this->cuboid;
        }
};

#endif // CUBE_H
