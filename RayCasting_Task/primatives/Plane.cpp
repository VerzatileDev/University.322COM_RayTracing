#include "Plane.h"

Plane::Plane()
{}

Plane::Plane(glm::vec3 CenterPosition, glm::vec3 Color, glm::vec3 normal)
{
    cen = CenterPosition;
    col = Color;
    nor = normal;
}

bool Plane::IntersectionOfPlane(glm::vec3 centre, glm::vec3 origin, glm::vec3 direction, glm::vec3 normal, float& t)
{
    denominator = glm::dot(normal, direction);
    if (denominator < 0.000001)
    {
        glm::vec3 p0I0 = centre - origin;
        t = glm::dot(p0I0, normal) / denominator;
        // t = -(I0 - p0) *n / I *n = ( p0 - I0) *n / I * n
        return(t >= 0);
    }
    return false;
}

#pragma region GetValue Data
glm::vec3 Plane::getCenter(void)
{
    return cen;
}


glm::vec3 Plane::getColor(void)
{
    return col;
}

glm::vec3 Plane::getNormal(void)
{
    return nor;
}
#pragma endregion