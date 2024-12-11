#ifndef CAMERA_H
#define CAMERA_H

#include <vector>
#include <iostream>
#include <map>
#include <glm/mat4x4.hpp>
#include <glm/vec4.hpp>
#include <glm/vec3.hpp>

#include "Cube.h"

class Camera {
    private: 
        glm::vec4 viewOrigin;
        glm::vec4 viewDir;
        glm::vec4 viewUp;
        float fFocus;

        std::vector<Cube*> cubes;

        void setPose(const glm::mat4& mat);

    public:
        Camera(glm::vec3 position, float focus)
         : fFocus(focus) {
            viewOrigin = glm::vec4(position, 1);

            viewDir = glm::vec4({0, 1, 0, 0});
            viewUp = glm::vec4({1, 0, 0, 0});
        }

        ~Camera() {
            for(auto cube : cubes) {
                delete cube;
            }
        }

        void addCube(Cube* cube) {
            cubes.push_back(cube);
        }
        void setCubes(std::vector<Cube*> cubes) {
            this->cubes = cubes;
        }
        void render();

        float addFocus(float focus) {
            return fFocus += focus;
        }

        void rotateLocalX(float theta);
        void rotateLocalY(float theta);
        void rotateLocalZ(float theta);

        void rotateWorldX(float theta);
        void rotateWorldY(float theta);
        void rotateWorldZ(float theta);

        void setPos(glm::vec3 pos) {
            viewOrigin = glm::vec4(pos, 1);
        }
        void addX(float x);
        void addY(float y);
        void addZ(float z);

        void handleKey(std::map<unsigned char, bool> keyStates);
};

#endif // CAMERA_H
