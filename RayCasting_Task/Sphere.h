#pragma once
#include "stdafx.h"

class Sphere
{
public:
	Sphere(float, glm::vec3, glm::vec3);
	~Sphere();

	bool IntersectionOfSphere(glm::vec3,float,glm::vec3, glm::vec3, float& t);
	glm::vec3 GetPosition(void);
	glm::vec3 GetColor(void);
	float GetRadius(void);
	
private:
	glm::vec3 cen;
	glm::vec3 col;
	float r;

};