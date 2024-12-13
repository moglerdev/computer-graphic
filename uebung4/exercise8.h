#pragma once

#include <glm/glm.hpp>
#include <cmath>
#include "Sphere.h"

// Function to compute the intersection of a sphere with a ray
glm::vec3 intersectSphere(Sphere sphere, glm::vec3 EyePos, glm::vec3 ViewDir) {
    // Calculate the quadratic coefficients for the ray-sphere intersection
    glm::vec3 L = EyePos - sphere.getCenter();
    float a = glm::dot(ViewDir, ViewDir);          // Coefficient for t^2
    float b = 2.0f * glm::dot(ViewDir, L);         // Coefficient for t
    float c = glm::dot(L, L) - sphere.getRadius() * sphere.getRadius(); // Constant term

    // Solve the quadratic equation for t
    float discriminant = b * b - 4.0f * a * c;

    if (discriminant < 0.0f) {
        // No intersection: return a point with a negative third coordinate
        return glm::vec3(0.0f, 0.0f, -1.0f);
    } else {
        // Compute the two solutions for t
        float t1 = (-b - sqrt(discriminant)) / (2.0f * a);
        float t2 = (-b + sqrt(discriminant)) / (2.0f * a);

        // Use the closest positive t value
        float t = (t1 > 0.0f) ? t1 : t2;

        if (t < 0.0f) {
            // Both intersections are behind the ray origin
            return glm::vec3(0.0f, 0.0f, -1.0f);
        }

        // Compute the intersection point
        glm::vec3 intersectionPoint = EyePos + t * ViewDir;

        // Return the intersection point (z coordinate will be non-negative)
        return intersectionPoint;
    }
}
