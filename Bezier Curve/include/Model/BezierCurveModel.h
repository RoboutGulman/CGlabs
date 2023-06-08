#pragma once
#include "stdafx.h"

#include "Primitives/BezierCurve.h"

#include <stdexcept>
#include <vector>

class BezierCurveModel
{
public:
	BezierCurveModel(BezierCurvePoints points)
		: m_points(points.p1, points.p2, points.p3, points.p4)
	{
	}

	BezierCurvePoints GetPoints()
	{
		return m_points;
	}

	std::vector<glm::vec2*> GetPointsPtr()
	{
		return { &m_points.p1, &m_points.p2, &m_points.p3, &m_points.p4 };
	}

private:
	BezierCurvePoints m_points;
};
