#pragma once
#include "../IPolytopeDrawable.h"
#include "../model/Cube/Cube.h"
#include "../model/Cube/TextureCube.h"
#include "../model/Pyramid/Pyramid.h"
#include "../model/Pyramid/TexturedPyramid.h"
#include "BaseRoom.h"
#include <memory>

class LivingRoom : public BaseRoom
{
public:
	LivingRoom()
	{
		std::unique_ptr<IPolytopeDrawable> room = std::make_unique<TextureCube>(std::move(std::make_unique<Cube>(1.3f, 1.3f, 1, glm::vec3{ 0, 0.3f, 0 })), "include\\model\\assets\\accentBrickwall.jpg");
		std::unique_ptr<IPolytopeDrawable> window = std::make_unique<TextureCube>(std::move(std::make_unique<Cube>(0.1f, 0.5f, 0.5f, glm::vec3{ -1.3f, 0, 0 })), "include\\model\\assets\\window.jpg");
		std::unique_ptr<IPolytopeDrawable> door = std::make_unique<TextureCube>(std::move(std::make_unique<Cube>(0.1f, 0.8f, 0.7f, glm::vec3{ 1.25f, -0.2f, 0 })), "include\\model\\assets\\door.jpg");
		std::unique_ptr<IPolytopeDrawable> roof = std::make_unique<TexturePyramid>(std::move(std::make_unique<Pyramid>(1.4f, 1.4f, 1, glm::vec3{ 0, 1.6f, 0 })), "include\\model\\assets\\roof.jpg");
		std::unique_ptr<IPolytopeDrawable> veranda = std::make_unique<TexturePyramid>(std::move(std::make_unique<Pyramid>(0.4f, 0.4f, 0.8f, glm::vec3{ 1.3f, 0.7f, 0 })), "include\\model\\assets\\roof.jpg");

		m_roomParts.push_back(std::move(room));
		m_roomParts.push_back(std::move(window));
		m_roomParts.push_back(std::move(door));
		m_roomParts.push_back(std::move(roof));
		m_roomParts.push_back(std::move(veranda));
	}
};
