#pragma once
#include "stdafx.h"

#include <sstream>

struct PolytopeTriangle
{
	glm::vec3 p1, p2, p3;
	glm::vec3 color;
	glm::vec2 texture1, texture2, texture3;
};

inline std::istream& operator>>(std::istream& stream, PolytopeTriangle& triangle)
{
	stream >> triangle.p1.x >> triangle.p1.y >> triangle.p1.z;
	stream >> triangle.p2.x >> triangle.p2.y >> triangle.p2.z;
	stream >> triangle.p3.x >> triangle.p3.y >> triangle.p3.z;
	stream >> triangle.color.r >> triangle.color.g >> triangle.color.b;
	stream >> triangle.texture1.x >> triangle.texture1.y;
	stream >> triangle.texture2.x >> triangle.texture2.y;
	stream >> triangle.texture3.x >> triangle.texture3.y;

	return stream;
}

inline std::ostream& operator<<(std::ostream& stream, PolytopeTriangle const& triangle)
{
	stream << triangle.p1.x << ' ' << triangle.p1.y << ' ' << triangle.p1.z << std::endl;
	stream << triangle.p2.x << ' ' << triangle.p2.y << ' ' << triangle.p2.z << std::endl;
	stream << triangle.p3.x << ' ' << triangle.p3.y << ' ' << triangle.p3.z << std::endl;
	stream << triangle.color.r << ' ' << triangle.color.g << ' ' << triangle.color.b << std::endl;

	return stream;
}