#pragma once
#include "rooms/LivingRoom.h"

class Cottage
{
public:

	Cottage()
	{
	}

	void Draw(int width, int height) const
	{
		//m_livingRoom.Draw(m_shaderProgram, m_shaderUniformMap);
	}

	void UpdateVPMatrices(int width, int height) const
	{
	}

private:
	LivingRoom m_livingRoom;
};
