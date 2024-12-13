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
#include <glm/vec3.hpp>
#include "Color.h"


class Material {
private:
	Color ambient;
	Color diffuse;
	Color specular;
	double shininess;
public:
	Material(Color _ambient = Color(0.5, 0.5, 0.5), Color _diffuse = Color(0.5, 0.5, 0.5), Color _specular = Color(1.0, 1.0, 1.0), double _shininess = 28):
		ambient(_ambient),
		diffuse(_diffuse),
		specular(_specular),
		shininess(_shininess)
	{}

	Color getAmbient() const {
		return ambient;
	}

	Color getDiffuse() const {
		return diffuse;
	}
	
	Color getSpecular() const {
		return specular;
	}

	double getShininess() const {
		return shininess;
	}
};

class Sphere
{
private:
	double r;		// radius
	glm::vec3 M;		// midpoint
	Material mat;
public :
	Sphere(glm::vec3 _M, double _r, Material _mat = Material())
	 : M(_M), r(_r), mat(_mat)
	{}

	void   setRadius(double _r)
	{
		r = (_r>0)? _r: 0;
	}
	double getRadius() const { return r; }

	void   setCenter(glm::vec3 _M) { M = _M; }
	glm::vec3 getCenter() const { return M; }
	Material getMaterial() const {
		return mat;
	}
};
