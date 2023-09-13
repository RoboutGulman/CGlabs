#pragma once
#include "../../BasePolytope.h"

class Cube : public BasePolytope
{
public:
	Cube(float width, float height, float depth, glm::vec3 position, glm::vec3 angle = { 0.f, 0.f, 0.f })
		: BasePolytope("include\\model\\assets\\cube.txt", VERTEX_COUNT, width, height, depth, position, angle)
	{
	}

private:
	static const unsigned int VERTEX_COUNT = 36;
};
