#include "Triangle.h"

Triangle::Triangle()
{}

Triangle::~Triangle()
{}

Triangle::Triangle(glm::vec3 color, glm::vec3 v0, glm::vec3 v1, glm::vec3 v2)
{
	// 3 Points of the triangles
	vertexPoints[0] = v0;
	vertexPoints[1] = v1;
	vertexPoints[2] = v2;

	// Base colour Originally gets changed to SurfaceColor (Barycentric Weights	+ col )
	col = color;
}


glm::vec3 Triangle::GetVertexPoint(int select)
{
	return vertexPoints[select];
}

glm::vec3 Triangle::GetColor(void)
{
	return col;
}

bool Triangle::IntersectionOfTriangle(glm::vec3 direction, glm::vec3 origin, glm::vec3 v0, glm::vec3 v1, glm::vec3 v2, float& t)
{
	//Calculates Planes normals
	glm::vec3 v0v1 = v1 - v0;
	glm::vec3 v0v2 = v2 - v0;
	glm::vec3 N = cross(v0v1, v0v2);


	u = (glm::dot((origin - v0), (glm::cross(direction, v0v2)))) / glm::dot(v0v1, glm::cross(direction, v0v2));
	v = (glm::dot(direction, glm::cross(origin - v0, v0v1))) / glm::dot(v0v1, glm::cross(direction, v0v2));
	w = 1 - u - v;

	//Calculates parameter (d) using equation 2
	float d = -dot(N, v0);

	// Check if (Ray and plane) are parallel to each other.
	if (u < 0 || u > 1)
		return false;
	else if (v < 0 || (u + v) > 1)
		return false;
	else
	{
		// t = - N(A,B,C) * O + D / N(A,B,C) * R
		t = -(glm::dot(N, origin) + d) / glm::dot(N, origin);

		/* Define Eges, from Points */
		// Case 0
		glm::vec3 P = origin + t * direction; // Hit Dedection towards the Plane
		glm::vec3 C;

		// Case 1
		glm::vec3 edge0 = v1 - v0;
		glm::vec3 vp0 = P - v0;
		C = cross(edge0, vp0);
		if (dot(N, C) < 0) return false;

		// Case 2
		glm::vec3 edge1 = v2 - v1;
		glm::vec3 vp1 = P - v1;
		C = cross(edge1, vp1);
		if (dot(N, C) < 0) return false;

		// Case 3
		glm::vec3 edge2 = v0 - v2;
		glm::vec3 vp2 = P - v2;
		C = cross(edge1, vp2);
		if (dot(N, C) < 0) return false;
		return true;
	}
}