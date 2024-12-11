#include "cg_math.h"

#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <iostream>

// Crop a value x to the interval [l, u]
double crop(double x, double l, double u) {
    return glm::clamp(x, l, u);
}

// Crop all components of a glm::dvec3 to the interval [l, u]
glm::dvec3 crop(const glm::dvec3& x, double l, double u) {
    return glm::clamp(x, glm::dvec3(l), glm::dvec3(u));
}

Color crop(const Color& x, double l, double u) {
    return Color(
        glm::clamp(x.r, l, u),
        glm::clamp(x.g, l, u),
        glm::clamp(x.b, l, u)
    );
}

// Convert spherical coordinates to affine coordinates
// (x) PI <= XZ <= 2Pi (X)
// (y) 0 <= YZ <= PI (Y)
glm::dvec3 SphericalToAffine(const glm::dvec3& sphericalCoordinates) {
    const double radius = sphericalCoordinates[0];
    const double theta = sphericalCoordinates[1]; // azimuth
    const double phi = sphericalCoordinates[2];   // polar

    glm::dvec3 affineCoordinates;
    affineCoordinates.x = radius * sin(phi) * cos(theta);
    affineCoordinates.y = radius * cos(phi);
    affineCoordinates.z = radius * sin(phi) * sin(theta);

    std::cout << "Affine Coordinates: " << affineCoordinates.x << ", " 
              << affineCoordinates.y << ", " << affineCoordinates.z << std::endl;
    
    return affineCoordinates;
}
