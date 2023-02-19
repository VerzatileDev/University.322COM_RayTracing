#pragma once
#include "Shape.h"

class Sphere
{
public:
	Sphere(); // for virtual method and waht not lol
	Sphere(float, glm::vec3, glm::vec3);
	~Sphere();

	bool IntersectionOfSphere(glm::vec3 orig, glm::vec3 dir, float& t);
	glm::vec3 GetPosition(void);
	glm::vec3 GetColor(void);
	float GetRadius(void);
	
private:
	glm::vec3 center;
	glm::vec3 col;
	float r;

};