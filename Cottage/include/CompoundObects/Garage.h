#pragma once
#include "../IDrawable.h"
#include "../model/Cube/Cube.h"
#include "../model/Cube/TextureCube.h"
#include "../model/Pyramid/Pyramid.h"
#include "../model/Pyramid/TexturedPyramid.h"
#include "CompoundObject.h"
#include <memory>

class Garage : public CompoundObject
{
public:
	Garage()
	{
		std::unique_ptr<IDrawable> room = std::make_unique<TextureCube>(std::move(std::make_unique<Cube>(1, 1, 1, glm::vec3{ 0, 0, -4 })), "include\\model\\assets\\brickwall.jpg");
		std::unique_ptr<IDrawable> door = std::make_unique<TextureCube>(std::move(std::make_unique<Cube>(0.1f, 0.8f, 0.7f, glm::vec3{ 1.f, -0.2f, -4 })), "include\\model\\assets\\garageDoor.jpg");
		std::unique_ptr<IDrawable> roof = std::make_unique<TexturePyramid>(std::move(std::make_unique<Pyramid>(1.2f, 1.2f, 1, glm::vec3{ 0, 1, -4 })), "include\\model\\assets\\roof.jpg");

		m_parts.push_back(std::move(room));
		m_parts.push_back(std::move(door));
		m_parts.push_back(std::move(roof));
	}
};
