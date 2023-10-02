#pragma once
#include "stdafx.h"

#pragma once

class Controls
{
public:
	Controls(float x, float y, float sensitivity)
		: m_x(x)
		, m_y(y)
		, m_sensitivity(sensitivity)
	{
	}

	void Move(float x, float y)
	{
		m_x += x * m_sensitivity * m_zoomNormalized;
		m_y += y * m_sensitivity * m_zoomNormalized;
	}

	void Zoom()
	{
		m_zoom += 0.1f * 1.f / m_zoomNormalized;
		m_zoomNormalized = 1.0f / m_zoom;
	}

	void Unzoom()
	{
		if (m_zoom - 0.1 < 1.0)
		{
			return;
		}
		m_zoom -= 0.1f * 1.f / m_zoomNormalized;
		m_zoomNormalized = 1.0f / m_zoom;
	}
	float GetX()
	{
		return m_x;
	}
	float GetY()
	{
		return m_y;
	}

	float GetZoomNormalized()
	{
		return m_zoomNormalized;
	}

private:
	float m_x;
	float m_y;
	float m_sensitivity;
	float m_zoom = 1.0f;
	float m_zoomNormalized = 1.0f;
};
