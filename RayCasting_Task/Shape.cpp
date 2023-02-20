#include "Shape.h"

Shape::Shape()
{
}

bool Shape::IntersectionOfSphere(glm::vec3 center, float radius, glm::vec3 origin, glm::vec3 direction, float& t)
{
    return true; // Only write here, if you wish to overwrite Derived Class
}

bool Shape::IntersectionOfPlane(glm::vec3 centre, glm::vec3 origin, glm::vec3 direction, glm::vec3 normal, float& t)
{
    return false;
}