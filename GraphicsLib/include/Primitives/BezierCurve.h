#pragma once
#include "stdafx.h"

#include "VertexArray.h"
#include "VertexBuffer/DynamicVertexBuffer.h"
#include "VertexBufferLayout.h"

#include <iostream>
#include <vector>

struct BezierCurvePoints
{
	BezierCurvePoints(glm::vec2 p1, glm::vec2 p2, glm::vec2 p3, glm::vec2 p4)
		: p1(p1)
		, p2(p2)
		, p3(p3)
		, p4(p4)
	{
	}
	std::vector<glm::vec2> GetVector()
	{
		return { p1, p2, p3, p4 };
	}
	glm::vec2 p1, p2, p3, p4;
};

class BezierCurve
{
public:
	BezierCurve(glm::vec4 color, bool isFilled)
		: m_va()
		, VERTEX_COUNT(isFilled ? 201 : 200)
		, m_vb(nullptr, sizeof(glm::vec2) * VERTEX_COUNT)
		, m_ib(GetIndices(VERTEX_COUNT))
		, m_color(color)
		, m_isFilled(isFilled)
	{
		VertexBufferLayout layout;
		layout.Push<glm::vec2>(1);
		m_va.AddBuffer(m_vb, layout);
	}

	void Draw(const Renderer& renderer, Shader& shader, BezierCurvePoints points) const
	{
		shader.SetUniform4f("u_color", m_color);
		m_vb.AddVertices(GetCurveVertices(points));
		renderer.Draw(m_isFilled ? GL_TRIANGLE_FAN : GL_LINE_STRIP, m_va, m_ib, shader);
	}

private:
	unsigned int VERTEX_COUNT;
	VertexArray m_va;
	DynamicVertexBuffer m_vb;
	IndexBuffer m_ib;
	glm::vec4 m_color;
	bool m_isFilled;

	std::vector<glm::vec2> GetCurveVertices(BezierCurvePoints points) const
	{
		// P = (1-t)^3*P1 + 3*(1-t)^2*t*P2 + 3*(1-t)*t^2*P3 + t^3*P4
		std::vector<glm::vec2> vertices;

		const float alpha = 1.0f / VERTEX_COUNT;

		if (m_isFilled)
		{
			vertices.emplace_back(0.f, 0.f);
		}

		for (float t = 0.0f; t < 1.0f; t += alpha)
		{
			// отформатировать код, чтобы формула читалась лучше(устранить дублирование кода)
			glm::vec2 v = {
				pow((1.0f - t), 3) * points.p1.x + 3.0f * pow((1.0f - t), 2) * t * points.p2.x + 3.0f * (1 - t) * t * t * points.p3.x + pow(t, 3) * points.p4.x,
				pow((1.0f - t), 3) * points.p1.y + 3.0f * pow((1.0f - t), 2) * t * points.p2.y + 3.0f * (1 - t) * t * t * points.p3.y + pow(t, 3) * points.p4.y
			};
			vertices.emplace_back(std::move(v));
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
