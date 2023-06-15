#pragma once
#include "Primitives/BasePrimitive.h"
#include <Primitives/Ellipse.h>
#include <Primitives/Rectangle.h>
#include <Renderer.h>

class Grass
{
public:
	Grass(glm::vec3 position, float width, float height, unsigned int vertices, glm::vec4 color)
		: m_width(width)
		, m_height(height)
		, m_position(position)
		, m_vertices(vertices)
		, m_color(color)
	{
	}

	void Draw(const Renderer& renderer, Shader& shader) const
	{
		float radiusX = m_width / m_vertices;
		// float offset = static_cast<float>(m_vertices - 1) / 2;
		for (float i = 0; i <= m_vertices; ++i)
		{
			Ellipse circle({ m_position.x + i * radiusX, m_position.y, 0 }, radiusX / 2, m_height, m_color);
			circle.Draw(renderer, shader);
		}
		Rectangle grassBase({ m_position.x, m_position.y + m_height / 1.5, 0 }, m_width, radiusX / 2, m_color);
		grassBase.Draw(renderer, shader);
	}

private:
	glm::vec3 m_position;
	float m_width, m_height;
	unsigned int m_vertices;
	glm::vec4 m_color;
};
