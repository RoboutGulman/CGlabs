#pragma once
#include "Grass.h"
#include "rooms/Garage.h"
#include "rooms/LivingRoom.h"
#include "Fence.h"

class Cottage
{
public:
	Cottage()
	{
	}

	void Draw(const Renderer& renderer, Shader& shader) const
	{
		m_livingRoom.Draw(renderer, shader);
		m_grass.Draw(renderer, shader);
		m_garage.Draw(renderer, shader);
		m_fence.Draw(renderer, shader);
	}

private:
	LivingRoom m_livingRoom;
	Grass m_grass;
	Garage m_garage;
	Fence m_fence;
};
