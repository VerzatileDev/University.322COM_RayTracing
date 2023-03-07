#include "Shape.h"

Shape::Shape()
{
}

bool Shape::IntersectionOfSphere(glm::vec3 center, float radius, glm::vec3 origin, glm::vec3 direction, float& t)
{
    return true;
}

bool Shape::IntersectionOfPlane(glm::vec3 centre, glm::vec3 origin, glm::vec3 direction, glm::vec3 normal, float& t)
{
    return false;
}

bool Shape::IntersectionOfTriangle(glm::vec3 direction, glm::vec3 origin, glm::vec3 vector0, glm::vec3 vector1, glm::vec3 vector2, float& t)
{
    return true;
}