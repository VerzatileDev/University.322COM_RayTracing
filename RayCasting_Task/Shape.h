#pragma once
#include "include/glm/glm.hpp"

class Shape
{
public:
	Shape();
	virtual bool IntersectionOfSphere(glm::vec3 center, float radius, glm::vec3 origin, glm::vec3 direction, float& t);
};