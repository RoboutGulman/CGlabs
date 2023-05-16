#pragma once
#include "stdafx.h"

#include <sstream>

struct Triangle
{
	glm::vec3 p1, p2, p3;
	glm::vec4 color;
};

inline std::istream& operator>>(std::istream& stream, Triangle& triangle)
{
	stream >> triangle.p1.x >> triangle.p1.y >> triangle.p1.z;
	stream >> triangle.p2.x >> triangle.p2.y >> triangle.p2.z;
	stream >> triangle.p3.x >> triangle.p3.y >> triangle.p3.z;
	stream >> triangle.color.r >> triangle.color.g >> triangle.color.b >> triangle.color.a;

	return stream;
}

inline std::ostream& operator<<(std::ostream& stream, Triangle const& triangle)
{
	stream << triangle.p1.x << ' ' << triangle.p1.y << ' ' << triangle.p1.z << std::endl;
	stream << triangle.p2.x << ' ' << triangle.p2.y << ' ' << triangle.p2.z << std::endl;
	stream << triangle.p3.x << ' ' << triangle.p3.y << ' ' << triangle.p3.z << std::endl;
	stream << triangle.color.r << ' ' << triangle.color.g << ' ' << triangle.color.b << ' ' << triangle.color.a << std::endl;

	return stream;
}
