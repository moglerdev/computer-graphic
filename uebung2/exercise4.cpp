#include "exercise4.h"


CMat3f rotateHomogenous2dMat(const float theta) {
	CMat3f m;
	m.setRow(CVec3f(cos(theta), -sin(theta), 0), 0);
	m.setRow(CVec3f(sin(theta), cos(theta), 0), 1);
	m.setRow(CVec3f(0 , 0, 1), 2);
	return m;
}

CMat3f trans2dMat(const CVec2f& position) {
    CMat3f m;
    m.setRow(CVec3f(1, 0, position[0]), 0);
    m.setRow(CVec3f(0, 1, position[1]), 1);
    m.setRow(CVec3f(0, 0, 1), 2);
    return m;
}


CMat3f homogenousRotateAroundOrigin(Planet& planet, float theta) {
    CMat3f m = rotateHomogenous2dMat(theta);
    CVec3f prevPos = CVec3f(planet.getPosition(), 1);
    CVec3f newPos = m * prevPos;
    planet.setStaticPosition(newPos);
    return m;
}

void homogenousRotateAroundPoint(const CMat3f& pose, Planet& planet) {
    auto p = pose * CVec3f(planet.getPosition(), 1);
    planet.setStaticPosition(p);
}