#pragma once
#include "../../BasePolytope.h"

class Pyramid : public BasePolytope
{
public:
	Pyramid(float width, float height, float depth, glm::vec3 position, glm::vec3 angle = { 0.f, 0.f, 0.f })
		: BasePolytope("res\\assets\\pyramid.txt", VERTEX_COUNT, width, height, depth, position, angle)
	{
	}

private:
	static const unsigned int VERTEX_COUNT = 18;
};