#pragma once
#include "stdafx.h"

#include "PolytopeTriangle.h"
#include "PolytopeVertex.h"
#include <array>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

class PolytopeVerticesReader
{
public:
	PolytopeVerticesReader()
	{
	}

	void GetVerticesFromFile(const std::string& fileName, std::vector<PolytopeVertex>& vertices)
	{
		vertices.clear();

		int vertexIndex = 0;
		std::ifstream input;
		input.open(fileName);
		if (!input.is_open())
		{
			throw std::runtime_error("Failed to open file");
		}

		PolytopeTriangle triangle;

		while (input >> triangle)
		{
			vertices.emplace_back(triangle.p1, triangle.color, triangle.texture1);
			vertices.emplace_back(triangle.p2, triangle.color, triangle.texture2);
			vertices.emplace_back(triangle.p3, triangle.color, triangle.texture3);
		}
	}
};
