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


CMat3f homogenousRotateAroundOrigin(Planet& planet, const float theta) {
    CMat3f m = rotateHomogenous2dMat(theta);
    CVec3f prevPos = CVec3f(planet.getPosition(), 1);
    CVec3f newPos = m * prevPos;
    planet.setStaticPosition(newPos);
    return m;
}

CVec3f po = CVec3f(290, 0, 1);
float x = 0;
void homogenousRotateAroundPlanet(const Planet& toOrbit, Planet& planet, const float theta) {
    x += theta;
    CMat3f pose = trans2dMat(-toOrbit.getPosition());
    CMat3f pose2 = trans2dMat(toOrbit.getPosition());
    CMat3f rot = homogenousRotateAroundOrigin(planet, x);
    CVec3f loc = pose2 * rot * pose * po;
    planet.setStaticPosition(loc);
}