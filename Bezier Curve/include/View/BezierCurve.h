#pragma once
#include "stdafx.h"

#include "VertexArray.h"
#include "VertexBuffer/DynamicVertexBuffer.h"
#include "VertexBufferLayout.h"
#include "utils.h"

#include <iostream>
#include <vector>

class BezierCurve
{
public:
	BezierCurve()
		: m_va()
		, m_vb(nullptr, sizeof(glm::vec2) * VERTEX_COUNT)
		, m_ib(GetIndices(VERTEX_COUNT))
	{
		VertexBufferLayout layout;
		layout.Push<glm::vec2>(1);
		m_va.AddBuffer(m_vb, layout);
	}

	void Draw(const Renderer& renderer, Shader& shader, const std::vector<glm::vec2>& bezierPoints)
	{
		shader.SetUniform4f("u_color", 0.95f, 0.3f, 0.15f, 1.0f);
		m_vb.AddVertices(GetCurveVertices(bezierPoints));
		renderer.Draw(GL_LINE_STRIP, m_va, m_ib, shader);
	}

private:
	const unsigned int VERTEX_COUNT = 2000;
	VertexArray m_va;
	DynamicVertexBuffer m_vb;
	IndexBuffer m_ib;

	//передавать точки а не вектор
	std::vector<glm::vec2> GetCurveVertices(std::vector<glm::vec2> bezierPoints)
	{
		// P = (1-t)^3*P1 + 3*(1-t)^2*t*P2 + 3*(1-t)*t^2*P3 + t^3*P4
		std::vector<glm::vec2> vertices;

		if (bezierPoints.size() != 4)
		{
			throw std::invalid_argument("Number of points must be 4");
		}

		const float alpha = 1.0f / VERTEX_COUNT;

		for (float t = 0.0f; t < 1.0f; t += alpha)
		{
			//отформатировать код, чтобы формула читалась лучше(устранить дублирование кода)
			glm::vec2 v = {
				(1.0f - t) * (1.0f - t) * (1.0f - t) * bezierPoints[0].x + 3.0f * (1.0f - t) * (1.0f - t) * t * bezierPoints[1].x + 3.0f * (1 - t) * t * t * bezierPoints[2].x + t * t * t * bezierPoints[3].x,
				(1.0f - t) * (1.0f - t) * (1.0f - t) * bezierPoints[0].y + 3.0f * (1.0f - t) * (1.0f - t) * t * bezierPoints[1].y + 3.0f * (1 - t) * t * t * bezierPoints[2].y + t * t * t * bezierPoints[3].y
			};
			vertices.emplace_back(std::move(v));
		}
		return vertices;
	}
	
	
};
