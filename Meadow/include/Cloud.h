#pragma once
#include <Primitives/Circle.h>
#include <Renderer.h>

constexpr int CLOUDS_NUMBER = 4;

class Cloud
{
public:
	Cloud(glm::vec2 topLeftPoint, float width, float height)
		: m_topLeftPoint(topLeftPoint)
		, m_width(width)
		, m_height(height)
	{
	}

	void Draw(const Renderer& renderer, Shader& shader) const
	{
		Circle circle({ m_width / 1.5f, 0 }, m_topLeftPoint.x + m_width / 3, m_topLeftPoint.y + m_height / 3, { 1.0f, 1.0f, 1.0f, 1.0f });
		circle.Draw(renderer, shader);

		for (int i = 0; i < CLOUDS_NUMBER - 1; ++i)
		{
			Circle circle({ m_width / 2, m_height }, m_topLeftPoint.x + m_width / 4 * i, m_topLeftPoint.y, { 1.0f, 1.0f, 1.0f, 1.0f });
			circle.Draw(renderer, shader);
		}
	}

private:
	glm::vec2 m_topLeftPoint;
	float m_width, m_height;
};
