#include "../include/Vertex.h"

#include <exception>
#include <fstream>
#include <iostream>
#include <vector>

#include "../include/Triangle.h"

std::vector<Vertex> GetVerticesFromFile(const std::string& fileName)
{
	std::vector<Vertex> vertices;
	std::ifstream input;
	input.open(fileName);
	if (!input.is_open())
	{
		throw std::runtime_error("Failed to open file");
	}

	Triangle triangle;
	while (input >> triangle)
	{
		vertices.emplace_back(triangle.p1, triangle.color);
		vertices.emplace_back(triangle.p2, triangle.color);
		vertices.emplace_back(triangle.p3, triangle.color);
	}

	return vertices;
}
