#include "Triangle.h"

Triangle::Triangle()
{}

Triangle::~Triangle()
{}

Triangle::Triangle(glm::vec3 color, glm::vec3 v0, glm::vec3 v1, glm::vec3 v2, glm::vec3 n0, glm::vec3 n1, glm::vec3 n2)
{
	// 3 Points of the triangles
	vertexPoints[0] = v0;
	vertexPoints[1] = v1;
	vertexPoints[2] = v2;

	// Normals
	vertexNormal[0] = n0;
	vertexNormal[1] = n1;
	vertexNormal[2] = n2;

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

bool Triangle::IntersectionOfTriangle(glm::vec3 direction, glm::vec3 origin, glm::vec3 v0, glm::vec3 v1, glm::vec3 v2, float& t, glm::vec3& IntPt, glm::vec3& tNormvec)
{
	// Moller-Trumbore
	glm::vec3 v0v1 = v1 - v0;
	glm::vec3 v0v2 = v2 - v0;
	glm::vec3 N = cross(v0v1, v0v2);
	tNormvec = glm::normalize(N);
	

	// Barycentric coordinates) https://www.scratchapixel.com/lessons/3d-basic-rendering/ray-tracing-rendering-a-triangle/barycentric-coordinates.html
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
		// Equation 3
		// t = - N(A,B,C) * O + D / N(A,B,C) * R
		t = -(glm::dot(N, origin) + d) / glm::dot(N, origin);

		/* Define Eges, from Points */
		// Case 0
		glm::vec3 P = origin + t * direction; // Hit Dedection towards the Plane
		glm::vec3 C;

		IntPt = origin + t * direction;

		//https://www.scratchapixel.com/lessons/3d-basic-rendering/ray-tracing-rendering-a-triangle/ray-triangle-intersection-geometric-solution.html
		// Case 1 (Edge 0)
		glm::vec3 edge0 = v1 - v0;
		glm::vec3 vp0 = P - v0;
		C = cross(edge0, vp0);
		if (dot(N, C) < 0) return false;

		// Case 2 (Edge 1)
		glm::vec3 edge1 = v2 - v1;
		glm::vec3 vp1 = P - v1;
		C = cross(edge1, vp1);
		if (dot(N, C) < 0) return false;

		// Case 3 (Edge 2)
		glm::vec3 edge2 = v0 - v2;
		glm::vec3 vp2 = P - v2;
		C = cross(edge1, vp2);
		if (dot(N, C) < 0) return false;
		return true; // p is inside the triangle (Ray hits the triangle)
	}
}

void Triangle::ComputeTriangleColor(const float ambientIntensity, const glm::vec3 IntPt, const glm::vec3 lightPt, const glm::vec3 rayDirection, const glm::vec3 tNormvec, float& ColValue)
{

	glm::vec3 diffuseCol(0.9, 1.0, 0.2); // kd
	glm::vec3 specularCol(0.5, 0.5, 0.0); // ks
	float shininess(100);
	glm::vec3 lightColor(1.0, 1.0, 1.0);
	glm::vec3 lightDir = glm::normalize(lightPt - IntPt);
	glm::vec3 viewDir = glm::normalize(-rayDirection);
	glm::vec3 reflectDir = glm::reflect(-lightDir, tNormvec);

	// Ambient component  c = k * i
	glm::vec3 ambient = ambientIntensity * diffuseCol;

	// Diffuse component  c = k * i max (0, L * n )
	float diff = glm::max(glm::dot(tNormvec, lightDir), 0.0f);
	glm::vec3 diffuse = diff * diffuseCol;

	// Specular component
	float spec = pow(glm::max(glm::dot(reflectDir, viewDir), 0.0f), shininess);
	glm::vec3 specular = spec * specularCol;

	// Final color value
	glm::vec3 finalColor = (ambient + diffuse + specular) * lightColor;

	// Set the output color value
	ColValue = glm::length(finalColor);

}