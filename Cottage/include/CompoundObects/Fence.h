#pragma once
#include "../model/Cube/TextureCube.h"
#include "../model/Pyramid/TexturedPyramid.h"
#include "CompoundObject.h"

class Fence : public CompoundObject
{
public:
	Fence()
	{
		std::unique_ptr<IDrawable> rearFence = std::make_unique<TextureCube>(std::move(std::make_unique<Cube>(0.05f, 1.f, 5, glm::vec3{ -4, 0, -1 })), "include\\model\\assets\\fence.jpg");
		std::unique_ptr<IDrawable> leftFence = std::make_unique<TextureCube>(std::move(std::make_unique<Cube>(3, 1.f, 0.05f, glm::vec3{ -1, 0, 4 })), "include\\model\\assets\\fence.jpg");
		std::unique_ptr<IDrawable> rightFence = std::make_unique<TextureCube>(std::move(std::make_unique<Cube>(3, 1.f, 0.05f, glm::vec3{ -1, 0, -6 })), "include\\model\\assets\\fence.jpg");

		m_parts.push_back(std::move(rearFence));
		m_parts.push_back(std::move(leftFence));
		m_parts.push_back(std::move(rightFence));
	}
};
