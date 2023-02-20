#pragma once
#include "include/glm/glm.hpp"
#include <algorithm> // For Swap method

class Shape
{
public:
	Shape();
	virtual bool IntersectionOfSphere(glm::vec3 center, float radius, glm::vec3 origin, glm::vec3 direction, float& t);
	virtual bool IntersectionOfPlane(glm::vec3 centre, glm::vec3 origin, glm::vec3 direction, glm::vec3 normal, float& t);
};