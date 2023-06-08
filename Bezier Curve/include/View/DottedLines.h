#pragma once
#include "stdafx.h"

#include "IndexBuffer.h"
#include "VertexBuffer/DynamicVertexBuffer.h"
#include "VertexBufferLayout.h"
#include "utils.h"

class DottedLines
{
public:
	DottedLines(int width, int height)
		: m_va()
		, m_vb(nullptr, sizeof(glm::vec2) * (POINTS_COUNT - 1) * 2)
		, m_ib(GetIndices((POINTS_COUNT - 1) * 2))
		, m_shader("res/shaders/DoteLine.shader")
	{
		m_shader.Bind();
		m_shader.SetUniformMatrix4fv("m_model", glm::mat4(1.0f));
		m_shader.SetUniformMatrix4fv("m_view", glm::mat4(1.0f));
		m_shader.SetUniformMatrix4fv("m_projection", glm::ortho(0.0f, float(width), float(height), 0.0f, -1.0f, 100.0f));
		m_shader.SetUniform1f("u_dashSize", 10.0f);
		m_shader.SetUniform1f("u_gapSize", 10.0f);
		m_shader.SetUniform2f("u_resolution", float(width), float(height));
		m_shader.Unbind();
		VertexBufferLayout layout;
		layout.Push<glm::vec2>(1);
		m_va.AddBuffer(m_vb, layout);
	}

	void Draw(const Renderer& renderer, const std::vector<glm::vec2> bezierPoints)
	{
		m_vb.AddVertices(GetCurveVertices(bezierPoints));
		renderer.Draw(GL_LINES, m_va, m_ib, m_shader);
	}

private:
	const unsigned int POINTS_COUNT = 4;
	VertexArray m_va;
	DynamicVertexBuffer m_vb;
	IndexBuffer m_ib;
	Shader m_shader;

	std::vector<glm::vec2> GetCurveVertices(std::vector<glm::vec2> bezierPoints)
	{
		return { bezierPoints[0], bezierPoints[1], bezierPoints[1], bezierPoints[2], bezierPoints[2], bezierPoints[3] };
	}
};
