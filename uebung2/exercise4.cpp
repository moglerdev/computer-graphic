#include "exercise4.h"

CMat3f translate(const float tx, const float ty) {
    CMat3f m;
    m.setRow(CVec3f(1.f, 0.f, tx), 0);
    m.setRow(CVec3f(0.f, 1.f, ty), 1);
    m.setRow(CVec3f(0.f, 0.f, 1.f), 2);
    return m;
}

CMat3f translate(const CVec2f& position) {
    return translate(position[0], position[1]);
}

CMat3f rotate(float theta) {
    float c = cos(theta), s = sin(theta);
    CMat3f m;
    m.setRow(CVec3f(c, -s, 0), 0);
    m.setRow(CVec3f(s,  c, 0), 1);
    m.setRow(CVec3f(0,  0, 1), 2);
    return m;
}

CMat3f rotateAroundPoint(const float theta, const CVec2f position) {
    return translate(position) * rotate(theta) * translate(-position);
}

void homogenousRotateAroundOrigin(Planet& planet, const float theta) {
    CMat3f m = rotate(theta);
    planet.setPose(m);
}

void homogenousRotateAroundPlanet(const Planet& toOrbit, Planet& planet, const float theta) {
    CVec2f tO = toOrbit.getPosition();
    CMat3f transform = rotateAroundPoint(theta, tO);
    planet.setPose(transform);
}