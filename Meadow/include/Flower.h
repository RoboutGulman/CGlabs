#pragma once
#include "Primitives/BasePrimitive.h"
#include <Primitives/Ellipse.h>
#include <Renderer.h>

class Flower
{
public:
	Flower(glm::vec3 position, float width, float height, unsigned int vertices, glm::vec4 color)
		: m_width(width)
		, m_height(height)
		, m_position(position)
		, m_vertices(vertices)
		, m_color(color)
	{
	}

	void Draw(const Renderer& renderer, Shader& shader) const
	{
		for (unsigned int angle = 0, j = 0; angle < 180 && j < m_vertices; angle += 180 / m_vertices, ++j)
		{
			Ellipse circle(m_position, m_width, m_height, m_color, angle);
			circle.Draw(renderer, shader);
		}
		auto maxDimension = std::max(m_width, m_height);
		Ellipse circle(m_position, maxDimension / 2, maxDimension / 2, { 1.f, 1.f, 1.f, 1.f });
		circle.Draw(renderer, shader);
	}

private:
	glm::vec3 m_position;
	float m_width, m_height;
	unsigned int m_vertices;
	glm::vec4 m_color;
};
