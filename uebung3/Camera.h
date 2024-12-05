#ifndef CAMERA_H
#define CAMERA_H

#include <vector>
#include "Cube.h"

#include "Vector.h"
#include "Matrix.h"


class Camera {
    private: 
        CVec4f viewOrigin;
        CVec4f viewDir;
        CVec4f viewUp;
        float fFocus;

        std::vector<Cube*> cubes;

        void setPose(CMat4f pose) {
            viewDir = pose * viewDir;
            viewUp = pose * viewUp;
            viewDir.normalize();
            viewUp.normalize();
        }

    public:
        Camera(CVec3f position, float focus)
         : fFocus(focus) {
            viewOrigin = CVec4f(position, 1);

            viewDir = CVec4f({0, 0, 1, 0});
            viewUp = CVec4f({0, 1, 0, 0});
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

        void setPos(CVec3f pos) {
            viewOrigin = CVec4f(pos, 1);
        }
        void addX(float x);
        void addY(float y);
        void addZ(float z);

        void handleKey(const unsigned char key);
};

#endif // CAMERA_H
