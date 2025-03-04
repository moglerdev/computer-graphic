////////////////////////////////////////////////////////////////////////////
//																	      //
// Code framework for lecture computer graphics WS 2024/25		          //
//										                                  //
// A very simple color class                                              //
//										                                  //
// (c) Georg Umlauf						                                  //
//										                                  //
////////////////////////////////////////////////////////////////////////////
#pragma once

#include <glm/glm.hpp>
#include <iostream>

class Color {
public:
	double r, g, b;

public:

	Color(double r = 1.0, double g = 1.0, double b = 1.0);
	Color(const glm::vec3& color);

	double& operator [] (int i);
	Color   operator * (const glm::vec3& x) const;		// Hadamar product

	glm::vec3 toVec3() const { return glm::vec3(r, g, b); }
};

std::ostream& operator << (std::ostream& os, const Color& c);


const Color Red(1.0, 0.0, 0.0);
const Color Green(0.0, 1.0, 0.0);
const Color Blue(0.0, 0.0, 1.0);
const Color Yellow(1.0, 1.0, 0.0);
const Color Cyan(0.0, 1.0, 1.0);
const Color Magenta(1.0, 0.0, 1.0);
