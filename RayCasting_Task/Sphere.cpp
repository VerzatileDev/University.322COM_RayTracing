#include "Sphere.h"

Sphere::Sphere()
{}

Sphere::Sphere(float Radius, glm::vec3 CenterPosition, glm::vec3 Color)
{
	center = CenterPosition;
	r = Radius;
	col = Color;
}

Sphere::~Sphere()
{}

bool Sphere::IntersectionOfSphere(glm::vec3 origin, glm::vec3 direction, float& t)
{
	float t0, t1; // t If Ray Intersects to the pixel.

	glm::vec3 length = center - origin;
	float tca = dot(length, direction);

	if (tca < 0) return false;

	float d = dot(length, length) - tca * tca;
	if (d > (r * r)) return false;

	float thc = sqrt(r * r - d);
	t0 = tca - thc;
	t1 = tca + thc;

	if (t0 > t1) std::swap(t0, t1);

	if (t0 < 0)
	{
		t0 = t1;
		if (t0 < 0) return false;
	}

	t = t0;

	return true;
}

glm::vec3 Sphere::GetPosition(void)
{
	return center;
}

glm::vec3 Sphere::GetColor(void)
{
	return col;
}

float Sphere::GetRadius(void)
{
	return r;
}