#pragma once
#include "../model/Cube/TextureCube.h"
#include "../model/Pyramid/TexturedPyramid.h"
#include "CompoundObject.h"

class DiningRoom : public CompoundObject
{
public:
	DiningRoom()
	{
		std::unique_ptr<IDrawable> room = std::make_unique<TextureCube>(std::move(std::make_unique<Cube>(1.5, 1, 1, glm::vec3{ 0, 0, -2 })), "include\\model\\assets\\brickwall.jpg");
		std::unique_ptr<IDrawable> frontWindow = std::make_unique<TextureCube>(std::move(std::make_unique<Cube>(0.1f, 0.7f, 0.7f, glm::vec3{ 1.5f, 0, -2 })), "include\\model\\assets\\window.jpg");
		std::unique_ptr<IDrawable> rearWindow = std::make_unique<TextureCube>(std::move(std::make_unique<Cube>(0.1f, 0.7f, 0.7f, glm::vec3{ -1.5f, 0, -2 })), "include\\model\\assets\\window.jpg");
		std::unique_ptr<IDrawable> roof = std::make_unique<TexturePyramid>(std::move(std::make_unique<Pyramid>(1.7f, 1.2f, 1, glm::vec3{ 0, 1, -2 })), "include\\model\\assets\\roof.jpg");
		

		m_parts.push_back(std::move(room));
		m_parts.push_back(std::move(frontWindow));
		m_parts.push_back(std::move(rearWindow));
		m_parts.push_back(std::move(roof));
	}
};