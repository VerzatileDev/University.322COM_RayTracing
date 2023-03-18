#include "Sphere.h"


Sphere::Sphere()
{}

Sphere::Sphere(float Radius, glm::vec3 CenterPosition, glm::vec3 Color)
{
	cen = CenterPosition;
	r = Radius;
	col = Color;
}

Sphere::~Sphere()
{}

bool Sphere::IntersectionOfSphere(glm::vec3 center,float radius , glm::vec3 origin, glm::vec3 direction, float& t, glm::vec3& IntPt)
{
	float t0, t1; // t If Ray Intersects to the pixel.

	glm::vec3 length = center - origin;
	float tca = dot(length, direction);
	
	if (tca < 0) return false;

	float d = dot(length, length) - tca * tca;
	if (d > (radius * radius)) return false;

	float thc = sqrt(radius * radius - d);
	t0 = tca - thc;
	t1 = tca + thc;

	if (t0 > t1) std::swap(t0, t1);

	if (t0 < 0)
	{
		t0 = t1;
		if (t0 < 0) return false; // both negative
	}

	t = t0;
	IntPt = origin + t * direction;
	return true;
}

void Sphere::ComputeColor(const float ambientIntensity, const glm::vec3 IntPt, const glm::vec3 lightPt, const glm::vec3 rayDirection, float& ColValue)
{
	glm::vec3 lightToPt, reflectLigt, surNorm;
	float Ca, Cd, Cs, tt;
	lightToPt = glm::normalize(lightPt - IntPt);
	surNorm = glm::normalize(IntPt - cen);

	reflectLigt = 2 * (glm::dot(lightToPt, surNorm)) * surNorm - lightToPt;
	Ca = ambientIntensity;
	Cd = glm::max(0.0, (double)glm::dot(lightToPt, surNorm));

	tt = glm::max(0.0, (double)glm::dot(reflectLigt, -rayDirection));
	Cs = glm::pow(tt, 50) * 0.7;

	ColValue = Ca + Cd + Cs;
	if (ColValue > 0.0)
	{
		ColValue = 1.0;
	}
}

#pragma region GetValue Data
glm::vec3 Sphere::GetPosition(void)
{
	return cen;
}

glm::vec3 Sphere::GetColor(void)
{
	return col;
}

float Sphere::GetRadius(void)
{
	return r;
}
#pragma endregion