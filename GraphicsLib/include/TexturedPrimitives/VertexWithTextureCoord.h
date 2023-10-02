#pragma once
#include "../stdafx.h"

#include <vector>

struct VertexWithTextureCoord
{
	VertexWithTextureCoord(glm::vec3 coordinates, glm::vec2 textureCoord)
		: coordinates(coordinates)
		, textureCoord(textureCoord)
	{
	}
	glm::vec3 coordinates;
	glm::vec2 textureCoord;
};
