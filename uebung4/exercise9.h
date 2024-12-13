#pragma once

#include <glm/glm.hpp>
#include <algorithm>
#include "Color.h"


Material normal = Material();
Material brass = Material(
    Color(0.33,0.22,0.03),
    Color(0.78,0.57,0.11),
    Color(0.99,0.94,0.81),
    28.0
);
Material bronze = Material(
    Color(0.21,0.13,0.05),
    Color(0.71,0.43,0.18),
    Color(0.39,0.27,0.17),
    26.0
);

// Function to compute the color using Phong Illumination
Color illumination(Sphere sphere, glm::vec3 HitPos, glm::vec3 EyePos) {

    Material mat = sphere.getMaterial();
	// reflection coefficients
    Color materialAmbient = mat.getAmbient();
    Color materialDiffuse = mat.getDiffuse();  // Diffuse reflectivity
    Color materialSpecular = mat.getSpecular(); // Specular reflectivity
    float shininess = mat.getShininess();                      // Shininess factor

    // Define light properties
    glm::vec3 lightPos(10.0f, 10.0f, 10.0f);      // Light position
    glm::vec3 lightColor(1.0f, 1.0f, 1.0f);       // Light color
    glm::vec3 ambientLight(0.2f, 0.2f, 0.2f);     // Ambient light color

    // Compute the normal at the hit point (assume sphere at origin)
    glm::vec3 normal = glm::normalize(HitPos);

    // Compute light direction
    glm::vec3 lightDir = glm::normalize(lightPos - HitPos);

    // Compute view direction
    glm::vec3 viewDir = glm::normalize(EyePos - HitPos);

    // Compute reflection direction
    glm::vec3 reflectDir = glm::reflect(-lightDir, normal);

    // Ambient component
    glm::vec3 ambient = materialAmbient * ambientLight;

    // Diffuse component (Lambertian reflection)
    float diff = std::max(glm::dot(normal, lightDir), 0.0f);
    glm::vec3 diffuse = materialDiffuse * lightColor * diff;

    // Specular component
    float spec = std::pow(std::max(glm::dot(viewDir, reflectDir), 0.0f), shininess);
    glm::vec3 specular = materialSpecular * lightColor * spec;

    // Combine all components
    glm::vec3 resultColor = ambient + diffuse + specular;

    // Convert to Color and clamp
    Color color(resultColor.r, resultColor.g, resultColor.b);
    color.clamp();
    return color;
}
