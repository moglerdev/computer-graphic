#pragma once
#include <glm/vec3.hpp>
#include "Color.h"
#include <GL/glut.h>

class Light {
	private:
		glm::vec3 position;
		Color color;

	public:
		Light(glm::vec3 _pos, Color _color = Color(1.0, 1.0, 1.0)):
			position(_pos), color(_color)
		{}

		Light(double _radius, double _theta, double _phi, Color _color = Color(1.0, 1.0, 1.0)): color(_color) {
			position.x = _radius * sin(_phi) * cos(_theta);
			position.y = _radius * cos(_phi);
			position.z = _radius * sin(_phi) * sin(_theta);
		}

		glm::vec3 getPosition() const { return position; }
		Color getColor() const { return color; }
};

class Scene {
private:
    Light light;
    Color backgroundColor;

public:
    Scene(Light _light, Color _bkgrColor):
        light(_light),
        backgroundColor(_bkgrColor)
        {}

    
    // This function controls and triggers the rendering process
    void rayCast() 
    {
        glClearColor(backgroundColor[0], backgroundColor[1], backgroundColor[2]);

        glm::vec3 eyePoint = glm::vec3(0.0,0.0, A);	// eye-point
        glm::vec3 viewDir  = glm::vec3(0.0,0.0,-A);	// view-direction
        glm::vec3 hitPoint;
        Color  pixelColor;

        // iterate over the pixels
        for (int x = 0; x < TEX_RES_X; x++) {
            for (int y = 0; y < TEX_RES_Y; y++) {
                // convert viewport to view window
                viewDir[0] = -1 + 2*x / static_cast<float>(TEX_RES_X -1);
                viewDir[1] = -1 + 2*y / static_cast<float>(TEX_RES_Y -1);

                // compute scene point covered by pixel
                hitPoint = intersectSphere(eyePoint,viewDir);

                // compute pixel color
                pixelColor = backColor; // background color
                if (hitPoint[2] != -1) pixelColor = illumination(hitPoint, viewDir);

                // draw the pixel
                setPixel(glm::ivec2(x, y), pixelColor);
            }
        }
        cout << "raycast done" << endl;
    }

};