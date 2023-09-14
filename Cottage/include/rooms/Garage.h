#pragma once
#include "../IPolytopeDrawable.h"
#include "../model/Cube/Cube.h"
#include "../model/Cube/TextureCube.h"
#include "../model/Pyramid/Pyramid.h"
#include "../model/Pyramid/TexturedPyramid.h"
#include "BaseRoom.h"
#include <memory>

class Garage : public BaseRoom
{
public:
	Garage()
	{
		std::unique_ptr<IPolytopeDrawable> room = std::make_unique<TextureCube>(std::move(std::make_unique<Cube>(1, 1, 1, glm::vec3{ 0, 0, -4 })), "include\\model\\assets\\brickwall.jpg");
		std::unique_ptr<IPolytopeDrawable> door = std::make_unique<TextureCube>(std::move(std::make_unique<Cube>(0.1f, 0.8f, 0.7f, glm::vec3{ 1.f, -0.2f, -4 })), "include\\model\\assets\\garageDoor.png");
		std::unique_ptr<IPolytopeDrawable> roof = std::make_unique<TexturePyramid>(std::move(std::make_unique<Pyramid>(1.2f, 1.2f, 1, glm::vec3{ 0, 1, -4 })), "include\\model\\assets\\roof.jpg");

		m_roomParts.push_back(std::move(room));
		m_roomParts.push_back(std::move(door));
		m_roomParts.push_back(std::move(roof));
	}
};
