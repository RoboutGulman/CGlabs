#pragma once
#include "model/Cube/TextureCube.h"
#include "model/Pyramid/TexturedPyramid.h"
#include "rooms/BaseRoom.h"

class Grass : public BaseRoom
{
public:
	Grass()
	{
		std::unique_ptr<IPolytopeDrawable> surface = std::make_unique<TextureCube>(std::move(std::make_unique<Cube>(10, 0.1f, 10, glm::vec3{ 0, -1, -1 })), "include\\model\\assets\\grass.jpg");

		m_roomParts.push_back(std::move(surface));
	}
};
