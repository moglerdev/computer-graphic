////////////////////////////////////////////////////////////////////////////
//																	      //
// Code framework for lecture computer graphics WS 2024/25 assignment 2   //
//										                                  //
// A class for circular objects, e.g. planets                             //
//										                                  //
// (c) Georg Umlauf						                                  //
//										                                  //
////////////////////////////////////////////////////////////////////////////

#pragma once

#include "Vector.h"
#include "Color.h"
#include "Matrix.h"

#include <vector>

class Planet {
private:
	Color  color    = Red;
	int    radius   = 10;
	CVec2f position = CVec2f(0.0);
	Planet *child = nullptr;

public:
	Planet() { }
	Planet(Planet * _child) : child(_child) { }

	// getter
	Color  getColor   () const { return color; }
	int    getRadius  () const { return radius; }
	CVec2f getPosition() const { return position; }

	// setter
	void setColor   (const Color&  c) { color    = c; }
	void setRadius  (int           r) { radius   = std::max(1, r); }
	
	void setPosition(const CVec2f& p) {
		if (this->child != nullptr) {
			CVec2f cp = child->getPosition() - this->position;
			child->setPosition(cp + p);
		}
		this->position = p;
	}

	void setStaticPosition(const CVec2f& p) {
		this->position = p;
	}

	void setPose(const CMat3f& pose) {
		if (this->child != nullptr) {
			child->setPose(pose);
		} 
		this->position = pose * CVec3f(this->position, 1);
	}
	
	// draw
	void draw() const; // Implement in this method your Bresenham algorithm for circles 

};