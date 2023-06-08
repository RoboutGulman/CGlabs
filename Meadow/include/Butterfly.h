#pragma once
#include <Primitives/BezierCurve.h>
#include <Primitives/Circle.h>
#include <Renderer.h>

class Butterfly
{
public:
	Butterfly(glm::vec2 topLeftPoint, float width, float height)
		: m_topLeftPoint(topLeftPoint)
		, m_width(width)
		, m_height(height)
	{
	}

	void Draw(const Renderer& renderer, Shader& shader) const
	{
		DrawButterflyBody(renderer, shader);
	}

private:
	void DrawButterflyBody(const Renderer& renderer, Shader& shader) const
	{
		BezierCurvePoints points({ m_topLeftPoint.x + 0.f, m_topLeftPoint.y + 0.3f * m_height },
			{ m_topLeftPoint.x + 0.125f * m_width, m_topLeftPoint.y + 0.3f * m_height },
			{ m_topLeftPoint.x + 0.0725f * m_width, m_topLeftPoint.y - 0.15f * m_height },
			{ m_topLeftPoint.x + 0.f, m_topLeftPoint.y - 0.1f * m_height });

		BezierCurve bezier({ 1.0f, 1.0f, 1.0f, 1.0f });

		bezier.Draw(renderer, shader, points);
	}

	glm::vec2 m_topLeftPoint;
	float m_width, m_height;
};
