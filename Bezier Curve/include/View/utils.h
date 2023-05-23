#pragma once
#include "stdafx.h"

#include <vector>

std::vector<GLuint> GetIndices(size_t size)
{
	std::vector<GLuint> indices;
	for (size_t i = 0; i < size; ++i)
	{
		indices.push_back(i);
	}
	return indices;
}