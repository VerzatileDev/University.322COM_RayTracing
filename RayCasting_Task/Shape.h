#pragma once
#include "include/glm/glm.hpp"

class Shape
{
public:
	virtual bool intersectSphere (glm::vec3 origin, glm::vec3 direction, float& t);
};