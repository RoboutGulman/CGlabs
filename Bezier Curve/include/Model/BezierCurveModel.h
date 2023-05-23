#pragma once
#include "stdafx.h"
#include "glm/glm.hpp"
#include <stdexcept>
#include <vector>

class BezierCurveModel
{
public:
	BezierCurveModel(const glm::vec2& p1, const glm::vec2& p2, const glm::vec2& p3, const glm::vec2& p4)
		: m_p1(p1)
		, m_p2(p2)
		, m_p3(p3)
		, m_p4(p4)
	{
	}

	std::vector<glm::vec2> GetPoints()
	{
		return { m_p1, m_p2, m_p3, m_p4 };
	}

	std::vector<glm::vec2*> GetPointsPtr()
	{
		return { &m_p1, &m_p2, &m_p3, &m_p4 };
	}

private:
	glm::vec2 m_p1, m_p2, m_p3, m_p4;
};
