#pragma once
#include "stdafx.h"

#include <string>
#include <vector>

struct PolytopeVertex
{
	PolytopeVertex(glm::vec3 coordinates, glm::vec3 color, glm::vec2 textureCoord)
		: coordinates(coordinates)
		, color(color)
		, normals(glm::vec3(1.0))
		, textureCoord(textureCoord)
	{
	}
	glm::vec3 coordinates;
	glm::vec3 color;
	glm::vec3 normals;
	glm::vec2 textureCoord;
};
