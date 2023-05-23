#pragma once
#include "stdafx.h"

#include "IndexBuffer.h"
#include "VertexBuffer/StaticVertexBuffer.h"
#include "VertexBufferLayout.h"

class CoordinateSystem
{
public:
	CoordinateSystem(float width, float height)
		: m_va()
		, m_vb(GetPoints(width, height))
		, m_ib(GetIndices(VERTEX_COUNT))
	{
		VertexBufferLayout layout;
		layout.Push<glm::vec2>(1);
		m_va.AddBuffer(m_vb, layout);
	}

	void Draw(const Renderer& renderer, Shader& shader)
	{
		shader.SetUniform4f("u_color", 1.0f, 1.0f, 1.0f, 1.0f);
		renderer.Draw(GL_LINES, m_va, m_ib, shader);
	}

private:
	static const unsigned int VERTEX_COUNT = 2000;
	VertexArray m_va;
	StaticVertexBuffer m_vb;
	IndexBuffer m_ib;

	std::vector<glm::vec2> GetPoints(float width, float height)
	{
		std::vector<glm::vec2> vertices;
		vertices.push_back({ width / 2, 0 });
		vertices.push_back({ width / 2, height });

		vertices.push_back({ width / 2, 0 });
		vertices.push_back({ width / 2 - 10, 10 });
		vertices.push_back({ width / 2, 0 });
		vertices.push_back({ width / 2 + 10, 10 });

		const float scaleDivisionsLength = 50;
		for (float i = height; i > 0; i -= scaleDivisionsLength)
		{
			vertices.push_back({ width / 2 - 10, i });
			vertices.push_back({ width / 2 + 10, i });
		}

		vertices.push_back({ 0, height / 2 });
		vertices.push_back({ width, height / 2 });

		vertices.push_back({ width, height / 2 });
		vertices.push_back({ width - 10, height / 2 - 10 });
		vertices.push_back({ width, height / 2 });
		vertices.push_back({ width - 10, height / 2 + 10 });

		for (float i = width - scaleDivisionsLength; i > 0; i -= scaleDivisionsLength)
		{
			vertices.push_back({ i, height / 2 - 10 });
			vertices.push_back({ i, height / 2 + 10 });
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
