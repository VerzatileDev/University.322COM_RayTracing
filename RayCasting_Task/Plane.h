#pragma once
#include "Shape.h"

class Plane : public Shape
{
public:

	Plane();
	Plane(glm::vec3 CentrePosition, glm::vec3 Colour, glm::vec3 normal);
	bool IntersectionOfPlane(glm::vec3 centre, glm::vec3 origin, glm::vec3 direction, glm::vec3 normal, float& t);

	/* Deliver outside of class */
	glm::vec3 getCenter(void), getColor(void), getNormal(void);

protected:
	float denominator = 0;
	glm::vec3 cen, nor, col;
};