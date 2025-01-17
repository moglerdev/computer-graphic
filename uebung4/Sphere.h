/////////////////////////////////////////////////////////////
// 
// Framework for computer graphics assignement 4
// 
// A simple sphere class
// 
// (c) Georg Umlauf, 2022
// 
/////////////////////////////////////////////////////////////

#pragma once

#include <glm/glm.hpp>

class Sphere
{
private:
	double r;		// radius
	glm::vec3 M;		// midpoint

public :
	Sphere(glm::vec3 _M, double _r) : M(_M), r(_r) {}

	void   setRadius(double _r)       { r = (_r>0)? _r: 0; }
	double getRadius(         ) const { return r; }

	void   setCenter(glm::vec3 _M)       { M = _M; }
	glm::vec3 getCenter(         ) const { return M; }

};
