#pragma once
#include "stdafx.h"

#include <vector>
#include <string>

struct Vertex
{
	Vertex(glm::vec3 coordinates, glm::vec4 color)
		: coordinates(coordinates)
		, color(color)
	{
	}
	glm::vec3 coordinates;
	glm::vec4 color;
};

std::vector<Vertex> GetVerticesFromFile(const std::string& fileName);
