#include "Shape.h"

Shape::Shape()
{
}

Shape::~Shape()
{
}

bool Shape::IntersectionOfSphere(glm::vec3 center, float radius, glm::vec3 origin, glm::vec3 direction, float& t, glm::vec3& IntPt)
{
    return true;
}

bool Shape::IntersectionOfPlane(glm::vec3 centre, glm::vec3 origin, glm::vec3 direction, glm::vec3 normal, float& t)
{
    return false;
}

bool Shape::IntersectionOfTriangle(glm::vec3 direction, glm::vec3 origin, glm::vec3 vector0, glm::vec3 vector1, glm::vec3 vector2, float& t, glm::vec3& IntPt, glm::vec3& tNormvec)
{
    return true;
}

void Shape::ComputeTriangleColor(const float ambientIntensity, const glm::vec3 IntPt, const glm::vec3 lightPt, const glm::vec3 rayDirection, const glm::vec3 tNormvec, float& ColValue)
{
}

void Shape::ComputeColor(const float ambientIntensity, const glm::vec3 IntPt, const glm::vec3 lightPt, const glm::vec3 rayDirection, float& ColValue)
{
}