#pragma once
#include "../stdafx.h"

#include "../IndexBuffer.h"
#include "../VertexBuffer/StaticVertexBuffer.h"
#include "../VertexBufferLayout.h"

class Rectangle : BasePrimitive
{
public:
	Rectangle(glm::vec3 position, float width, float height, glm::vec4 color)
		: BasePrimitive(width, height, position)
		, m_va()
		, m_vb(GetPoints())
		, m_ib(GetIndices())
		, m_color(color)
	{
		VertexBufferLayout layout;
		layout.Push<glm::vec2>(1);
		m_va.AddBuffer(m_vb, layout);
	}

	void Draw(const Renderer& renderer, Shader& shader)
	{
		ApplyModelTransform(shader);
		shader.Bind();
		shader.SetUniform4f("u_color", m_color);
		renderer.Draw(GL_TRIANGLES, m_va, m_ib, shader);
		DisableModelTransform(shader);
	}

private:
	VertexArray m_va;
	StaticVertexBuffer m_vb;
	IndexBuffer m_ib;
	glm::vec4 m_color;

	std::vector<glm::vec2> GetPoints()
	{
		return {
			{ 0, 1.0f },
			{ 1.0f, 1.0f },
			{ 1.0f, 0.0f },
			{ 0.0f, 0.0f }
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
