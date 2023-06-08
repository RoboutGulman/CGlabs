#pragma once
#include "../stdafx.h"

#include "../IndexBuffer.h"
#include "../VertexBuffer/StaticVertexBuffer.h"
#include "../VertexBufferLayout.h"

class Rectangle
{
public:
	Rectangle(glm::vec2 topLeftPoint, float width, float height, glm::vec4 color)
		: m_va()
		, m_vb(GetPoints(topLeftPoint, width, height))
		, m_ib(GetIndices())
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
		renderer.Draw(GL_TRIANGLES, m_va, m_ib, shader);
	}

private:
	VertexArray m_va;
	StaticVertexBuffer m_vb;
	IndexBuffer m_ib;
	glm::vec4 m_color;

	std::vector<glm::vec2> GetPoints(glm::vec2 topLeftPoint, float width, float height)
	{
		return {
			{ topLeftPoint.x, topLeftPoint.y + height },
			{ topLeftPoint.x + width, topLeftPoint.y + height },
			{ topLeftPoint.x + width, topLeftPoint.y },
			topLeftPoint
		};
	}

	std::vector<GLuint> GetIndices()
	{
		return {
			0, 1, 2,
			2, 3, 0
		};
	}
};
