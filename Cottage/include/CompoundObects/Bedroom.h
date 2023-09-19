#pragma once
#include "../model/Cube/TextureCube.h"
#include "../model/Pyramid/TexturedPyramid.h"
#include "CompoundObject.h"

class Bedroom : public CompoundObject
{
public:
	Bedroom()
	{
		std::unique_ptr<IDrawable> room = std::make_unique<TextureCube>(std::move(std::make_unique<Cube>(1, 1, 1, glm::vec3{ 0, 0, 2 })), "res\\assets\\brickwall.jpg");
		std::unique_ptr<IDrawable> window = std::make_unique<TextureCube>(std::move(std::make_unique<Cube>(0.1f, 0.5f, 0.5f, glm::vec3{ 1, 0, 2 })), "res\\assets\\window.jpg");
		std::unique_ptr<IDrawable> roof = std::make_unique<TexturePyramid>(std::move(std::make_unique<Pyramid>(1.2f, 1.f, 1.2f, glm::vec3{ 0, 1, 2 })), "res\\assets\\roof.jpg");

		m_parts.push_back(std::move(room));
		m_parts.push_back(std::move(window));
		m_parts.push_back(std::move(roof));
	}
};
