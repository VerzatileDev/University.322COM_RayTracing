#ifndef VERTEX_H
#define VERTEX_H

#include "include/glm/glm.hpp"

struct Vertex
{
	glm::vec4 coords;
	glm::vec2 texCoords;
};

struct VertexWtihNormal
{
	glm::vec4 coords;
	glm::vec3 normals;
};

struct  VertexWithAll
{
	glm::vec3 position;
	glm::vec3 color;
	glm::vec2 textcoord;
	glm::vec3 normal;
};

#endif