#pragma once
#include "Primitives/BasePrimitive.h"
#include <Primitives/Ellipse.h>
#include <Renderer.h>

constexpr int CLOUDS_NUMBER = 4;

class Cloud
{
public:
	Cloud(glm::vec3 position, float width, float height)
		: m_width(width)
		, m_height(height)
		, m_position(position)
	{
	}

	void Draw(const Renderer& renderer, Shader& shader) const
	{
		Ellipse circle({ m_width / 1.5f, 0, 0 }, m_position.x + m_width / 3, m_position.y + m_height / 3, { 1.0f, 1.0f, 1.0f, 1.0f });
		circle.Draw(renderer, shader);

		for (int i = 0; i < CLOUDS_NUMBER - 1; ++i)
		{
			Ellipse circle({ m_width / 2, m_height, 0 }, m_position.x + m_width / 4 * i, m_position.y, { 1.0f, 1.0f, 1.0f, 1.0f });
			circle.Draw(renderer, shader);
		}
	}

private:
	glm::vec3 m_position;
	float m_width, m_height;
};
