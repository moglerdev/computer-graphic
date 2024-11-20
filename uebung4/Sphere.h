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

#include "Vector.h"

class Sphere
{
private:
	double r;		// radius
	CVec3d M;		// midpoint

public :
	Sphere(CVec3d _M, double _r) : M(_M), r(_r) {}

	void   setRadius(double _r)       { r = (_r>0)? _r: 0; }
	double getRadius(         ) const { return r; }

	void   setCenter(CVec3d _M)       { M = _M; }
	CVec3d getCenter(         ) const { return M; }

};
