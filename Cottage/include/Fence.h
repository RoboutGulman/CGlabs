#pragma once
#include "model/Cube/TextureCube.h"
#include "model/Pyramid/TexturedPyramid.h"
#include "rooms/BaseRoom.h"

class Fence : public BaseRoom
{
public:
	Fence()
	{
		std::unique_ptr<IPolytopeDrawable> rearFence = std::make_unique<TextureCube>(std::move(std::make_unique<Cube>(0.05f, 1.f, 5, glm::vec3{ -4, 0, -1 })), "include\\model\\assets\\fence.jpg");
		std::unique_ptr<IPolytopeDrawable> leftFence = std::make_unique<TextureCube>(std::move(std::make_unique<Cube>(0.05f, 1.f, 3, glm::vec3{ -1, 0, 4 })), "include\\model\\assets\\fence.jpg");
		std::unique_ptr<IPolytopeDrawable> rightFence = std::make_unique<TextureCube>(std::move(std::make_unique<Cube>(0.05f, 1.f, 3, glm::vec3{ -1, 0, -6 })), "include\\model\\assets\\fence.jpg");
		

		m_roomParts.push_back(std::move(rearFence));
		m_roomParts.push_back(std::move(leftFence));
		m_roomParts.push_back(std::move(rightFence));
	}

};