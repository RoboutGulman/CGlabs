#pragma once
#include "../model/Cube/TextureCube.h"
#include "../model/Pyramid/TexturedPyramid.h"
#include "CompoundObject.h"

class Grass : public CompoundObject
{
public:
	Grass()
	{
		std::unique_ptr<IDrawable> surface = std::make_unique<TextureCube>(std::move(std::make_unique<Cube>(10, 0.1f, 10, glm::vec3{ 0, -1, -1 })), "include\\model\\assets\\grass.jpg");

		m_parts.push_back(std::move(surface));
	}
};
