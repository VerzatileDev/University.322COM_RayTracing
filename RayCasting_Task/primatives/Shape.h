#pragma once
#include "glm/glm.hpp"
#include <algorithm> // For Swap method

class Shape
{
public:
	Shape();
	// Only write here, if you wish to overwrite Derived Class
	virtual bool IntersectionOfSphere(glm::vec3 center, float radius, glm::vec3 origin, glm::vec3 direction, float& t);
	virtual bool IntersectionOfPlane(glm::vec3 centre, glm::vec3 origin, glm::vec3 direction, glm::vec3 normal, float& t);
	virtual bool IntersectionOfTriangle(glm::vec3 direction, glm::vec3 origin, glm::vec3 vector0, glm::vec3 vector1, glm::vec3 vector2, float& t);
};