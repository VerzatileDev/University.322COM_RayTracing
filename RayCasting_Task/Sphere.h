#pragma once
#include "Shape.h"
#include "include/glm/glm.hpp"
#include <algorithm> // For Swap method

class Sphere : public Shape
{
public:
	Sphere(); // Default Contstructor for Virtual methods.
	Sphere(float, glm::vec3, glm::vec3);
	~Sphere();

	bool IntersectionOfSphere(glm::vec3 center, float radius, glm::vec3 origin, glm::vec3 direction, float& t);
	glm::vec3 GetPosition(void);
	glm::vec3 GetColor(void);
	float GetRadius(void);
	
private:
	glm::vec3 cen;
	glm::vec3 col;
	float r;

};