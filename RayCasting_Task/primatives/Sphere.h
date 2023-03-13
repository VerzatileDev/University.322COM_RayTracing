#pragma once
#include "Shape.h"

class Sphere : public Shape
{
public:
	Sphere();
	Sphere(float Radius, glm::vec3 CenterPosition, glm::vec3 Color);
	~Sphere();

	bool IntersectionOfSphere(glm::vec3 center, float radius, glm::vec3 origin, glm::vec3 direction, float& t, glm::vec3& IntPt);
	void ComputeColor(const float ambientIntensity, const glm::vec3 IntPt, const glm::vec3 lightPt, const glm::vec3 rayDirection, float& ColValue);
	
	/* Deliver Outside of Class */	
	glm::vec3 GetPosition(void), GetColor(void);
	float GetRadius(void);
protected:
	glm::vec3 cen,col;
	float r;
};