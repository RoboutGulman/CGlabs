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
		Ellipse circle({ m_position.x + m_width / 1.5f, m_position.y + m_height / 2, 0 }, m_width, m_height / 2, { 1.0f, 1.0f, 1.0f, 1.0f });
		circle.Draw(renderer, shader);

		for (int i = 0; i < CLOUDS_NUMBER - 1; ++i)
		{
			Ellipse circle({ m_position.x + m_width / 2 * i, m_position.y , 0 }, m_width / 4, m_height / 3, { 1.0f, 1.0f, 1.0f, 1.0f });
			circle.Draw(renderer, shader);
		}
	}

private:
	glm::vec3 m_position;
	float m_width, m_height;
};
