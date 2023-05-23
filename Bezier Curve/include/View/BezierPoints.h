#pragma once
#include "stdafx.h"

#include "IndexBuffer.h"
#include "VertexBuffer/DynamicVertexBuffer.h"
#include "VertexBufferLayout.h"
#include "utils.h"

class BezierPoints
{
public:
	BezierPoints()
		: m_va()
		, m_vb(nullptr, sizeof(glm::vec2) * POINTS_COUNT)
		, m_ib(GetIndices(POINTS_COUNT))
	{
		VertexBufferLayout layout;
		layout.Push<glm::vec2>(1);
		m_va.AddBuffer(m_vb, layout);
	}

	void Draw(const Renderer& renderer, Shader& shader, const std::vector<glm::vec2> vertices)
	{
		shader.SetUniform4f("u_color", 0.15f, 0.3f, 0.95f, 1.0f);
		m_vb.AddVertices(vertices);
		GLCall(glPointSize(10.0f));
		renderer.Draw(GL_POINTS, m_va, m_ib, shader);
		GLCall(glPointSize(1.0f));
	}

private:
	const unsigned int POINTS_COUNT = 4;
	VertexArray m_va;
	DynamicVertexBuffer m_vb;
	IndexBuffer m_ib;
};
