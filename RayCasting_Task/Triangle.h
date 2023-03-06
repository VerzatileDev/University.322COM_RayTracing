#pragma once
#include "Shape.h"

class Triangle : public Shape
{
public:
	Triangle();   // For Virtual Method (Empty)
	~Triangle(); // For Clean-up
	Triangle(glm::vec3 color, glm::vec3 point0, glm::vec3 point1, glm::vec3 point2); // Base Constructor
	
	bool IntersectionOfTriangle(glm::vec3 direction, glm::vec3 origin, glm::vec3 vector0, glm::vec3 vector1, glm::vec3 vector2, float& t); // Locate if an interesection is Present (Ray to the Element)

	glm::vec3 GetVertexPoint(int select);
	glm::vec3 GetColor(void);
	glm::vec3 vertexPoints[3]{ v0, v1, v2 };

protected:
	glm::vec3 v0, v1, v2;            // Triangle Point Positions (vertex Points)
	glm::vec3 col;                  // Colour Properties         (Colour Vector)
	glm::vec3 norm0, norm1, norm2; // Triangle Light Properties  (Triangle Normals)
	float v = 0, u = 0, w = 0;    // Surface Colour From Light   (Additionally added on top of "col" Including light properties) Barycentric Weights u,v,w. 
};