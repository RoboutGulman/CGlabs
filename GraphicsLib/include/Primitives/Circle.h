#pragma once
#include "../stdafx.h"

#include "../IndexBuffer.h"
#include "../VertexBuffer/StaticVertexBuffer.h"
#include "../VertexBufferLayout.h"

class Circle
{
public:
	Circle(glm::vec2 topLeftPoint, float width, float height, glm::vec4 color)
		: m_va()
		, m_vb(GetPoints(topLeftPoint, width, height))
		, m_ib(GetIndices(VERTEX_COUNT))
		, m_color(color)
	{
		VertexBufferLayout layout;
		layout.Push<glm::vec2>(1);
		m_va.AddBuffer(m_vb, layout);
	}

	void Draw(const Renderer& renderer, Shader& shader)
	{
		shader.Bind();
		shader.SetUniform4f("u_color", m_color);
		renderer.Draw(GL_TRIANGLE_FAN, m_va, m_ib, shader);
	}

private:
	VertexArray m_va;
	StaticVertexBuffer m_vb;
	IndexBuffer m_ib;
	glm::vec4 m_color;
	static const unsigned int VERTEX_COUNT = 360;

	std::vector<glm::vec2> GetPoints(glm::vec2 topLeftPoint, float width, float height)
	{
		std::vector<glm::vec2> vertices;

		for (int angle = 0; angle < 360; angle++)
		{
			float rad = static_cast<float>(angle * M_PI / 180.0f);
			// positions
			vertices.push_back({ topLeftPoint.x + width + cosf(rad) * width, topLeftPoint.y + height + sinf(rad) * height });
		}

		return vertices;
	}

	std::vector<GLuint> GetIndices(size_t size)
	{
		std::vector<GLuint> indices;
		for (size_t i = 0; i < size; ++i)
		{
			indices.push_back(i);
		}
		return indices;
	}
};
